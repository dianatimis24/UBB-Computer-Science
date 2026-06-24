using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace lab1_DBMS
{
    public partial class Form1 : Form
    {
        SqlConnection connection;
        SqlDataAdapter daArtStyle;
        SqlDataAdapter daArtist;
        DataSet dset;
        BindingSource bsArtStyles;
        BindingSource bsArtists;
        SqlCommandBuilder cmdBuilder;

        string queryArtStyle;
        string queryArtist;
        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData() // fill the form with the data from the database
        {
            try
            {
                connection = new SqlConnection(getConnectionString());

                queryArtStyle = "SELECT * FROM ArtStyles";
                queryArtist = "SELECT * FROM Artists";

                daArtStyle = new SqlDataAdapter(queryArtStyle, connection);
                daArtist = new SqlDataAdapter(queryArtist, connection);
                dset = new DataSet();
                daArtStyle.Fill(dset, "ArtStyles");
                daArtist.Fill(dset, "Artists");

                cmdBuilder = new SqlCommandBuilder(daArtist);

                dset.Relations.Add("ArtStylesArtists",
                    dset.Tables["ArtStyles"].Columns["asID"],
                    dset.Tables["Artists"].Columns["asID"]);

                this.artstylesDataGridView.DataSource = dset.Tables["ArtStyles"];
                this.artistsDataGridView.DataSource = this.artstylesDataGridView.DataSource;
                this.artistsDataGridView.DataMember = "ArtStylesArtists";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        string getConnectionString()
        {
            return "Data Source=DIANA_TIMIS\\SQLEXPRESS;Initial Catalog=MyArtMuseum;Integrated Security=True;Encrypt=False";
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                daArtist.Update(dset, "Artists");
                MessageBox.Show("Changes saved successfully!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
