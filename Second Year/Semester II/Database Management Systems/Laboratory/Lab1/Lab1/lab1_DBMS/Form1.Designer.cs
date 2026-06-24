namespace lab1_DBMS
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Artists = new System.Windows.Forms.Label();
            this.artstylesDataGridView = new System.Windows.Forms.DataGridView();
            this.artistsDataGridView = new System.Windows.Forms.DataGridView();
            this.label2 = new System.Windows.Forms.Label();
            this.updateButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.artstylesDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // Artists
            // 
            this.Artists.AutoSize = true;
            this.Artists.Location = new System.Drawing.Point(45, 38);
            this.Artists.Name = "Artists";
            this.Artists.Size = new System.Drawing.Size(104, 25);
            this.Artists.TabIndex = 0;
            this.Artists.Text = "Art Styles";
            // 
            // artstylesDataGridView
            // 
            this.artstylesDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.artstylesDataGridView.Location = new System.Drawing.Point(50, 82);
            this.artstylesDataGridView.Name = "artstylesDataGridView";
            this.artstylesDataGridView.RowHeadersWidth = 82;
            this.artstylesDataGridView.RowTemplate.Height = 33;
            this.artstylesDataGridView.Size = new System.Drawing.Size(774, 555);
            this.artstylesDataGridView.TabIndex = 1;
            // 
            // artistsDataGridView
            // 
            this.artistsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.artistsDataGridView.Location = new System.Drawing.Point(884, 82);
            this.artistsDataGridView.Name = "artistsDataGridView";
            this.artistsDataGridView.RowHeadersWidth = 82;
            this.artistsDataGridView.RowTemplate.Height = 33;
            this.artistsDataGridView.Size = new System.Drawing.Size(779, 555);
            this.artistsDataGridView.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(879, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 25);
            this.label2.TabIndex = 2;
            this.label2.Text = "Artists";
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(757, 709);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(167, 91);
            this.updateButton.TabIndex = 4;
            this.updateButton.Text = "UPDATE";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1716, 831);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.artistsDataGridView);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.artstylesDataGridView);
            this.Controls.Add(this.Artists);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.artstylesDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Artists;
        private System.Windows.Forms.DataGridView artstylesDataGridView;
        private System.Windows.Forms.DataGridView artistsDataGridView;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button updateButton;
    }
}

