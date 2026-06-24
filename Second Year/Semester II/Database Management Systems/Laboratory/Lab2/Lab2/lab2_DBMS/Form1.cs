using System;
using System.Data;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;

namespace lab2_DBMS
{
    public partial class Form1 : Form
    {
        SqlConnection connection;
        SqlDataAdapter daParent;
        SqlDataAdapter daChild;
        DataSet dset;
        SqlCommandBuilder cmdBuilder;

        string ConnectionString { get => ConfigurationManager.ConnectionStrings["MyArtMuseum"].ConnectionString; }
        string Scenario { get => ConfigurationManager.AppSettings["CurrentScenario"]; }

        string parentTable;
        string childTable;
        string foreignKey;
        string parentQuery;
        string childQuery;

        public Form1()
        {
            InitializeComponent();
            LoadData();
        }

        void LoadData()
        {
            try
            {
                this.Text = ConfigurationManager.AppSettings[Scenario + "_Caption"];

                parentTable = ConfigurationManager.AppSettings[Scenario + "_ParentTable"];
                childTable = ConfigurationManager.AppSettings[Scenario + "_ChildTable"];
                foreignKey = ConfigurationManager.AppSettings[Scenario + "_ForeignKey"];
                parentQuery = $"SELECT * FROM {parentTable}";
                childQuery = $"SELECT * FROM {childTable}";

                connection = new SqlConnection(ConnectionString);
                dset = new DataSet();

                daParent = new SqlDataAdapter(parentQuery, connection);
                daChild = new SqlDataAdapter(childQuery, connection);

                cmdBuilder = new SqlCommandBuilder(daChild);

                daParent.Fill(dset, parentTable);
                daChild.Fill(dset, childTable);

                DataRelation relation = new DataRelation(
                    "ParentChildRelation",
                    dset.Tables[parentTable].Columns[foreignKey],
                    dset.Tables[childTable].Columns[foreignKey]
                );
                dset.Relations.Add(relation);

                parentLabel.Text = parentTable;
                childLabel.Text = childTable;
                parentDataGridView.DataSource = dset.Tables[parentTable];
                childDataGridView.DataSource = parentDataGridView.DataSource;
                childDataGridView.DataMember = "ParentChildRelation";
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error loading data: " + ex.Message);
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                this.Validate();
                childDataGridView.EndEdit();
                childTable = ConfigurationManager.AppSettings[Scenario + "_ChildTable"];
                int rowsAffected = daChild.Update(dset, childTable);

                MessageBox.Show($"{rowsAffected} row(s) updated successfully!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Update failed: " + ex.Message);
            }
        }
    }
}