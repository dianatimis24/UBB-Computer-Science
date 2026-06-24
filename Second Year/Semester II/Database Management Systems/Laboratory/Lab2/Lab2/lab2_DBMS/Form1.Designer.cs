namespace lab2_DBMS
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
            this.updateButton = new System.Windows.Forms.Button();
            this.childDataGridView = new System.Windows.Forms.DataGridView();
            this.parentDataGridView = new System.Windows.Forms.DataGridView();
            this.parentLabel = new System.Windows.Forms.Label();
            this.childLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(737, 708);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(167, 91);
            this.updateButton.TabIndex = 9;
            this.updateButton.Text = "UPDATE";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // childDataGridView
            // 
            this.childDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childDataGridView.Location = new System.Drawing.Point(864, 81);
            this.childDataGridView.Name = "childDataGridView";
            this.childDataGridView.RowHeadersWidth = 82;
            this.childDataGridView.RowTemplate.Height = 33;
            this.childDataGridView.Size = new System.Drawing.Size(779, 555);
            this.childDataGridView.TabIndex = 8;
            // 
            // parentDataGridView
            // 
            this.parentDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentDataGridView.Location = new System.Drawing.Point(30, 81);
            this.parentDataGridView.Name = "parentDataGridView";
            this.parentDataGridView.RowHeadersWidth = 82;
            this.parentDataGridView.RowTemplate.Height = 33;
            this.parentDataGridView.Size = new System.Drawing.Size(774, 555);
            this.parentDataGridView.TabIndex = 6;
            // 
            // parentLabel
            // 
            this.parentLabel.AutoSize = true;
            this.parentLabel.Location = new System.Drawing.Point(30, 22);
            this.parentLabel.Name = "parentLabel";
            this.parentLabel.Size = new System.Drawing.Size(70, 25);
            this.parentLabel.TabIndex = 10;
            this.parentLabel.Text = "label1";
            // 
            // childLabel
            // 
            this.childLabel.AutoSize = true;
            this.childLabel.Location = new System.Drawing.Point(864, 22);
            this.childLabel.Name = "childLabel";
            this.childLabel.Size = new System.Drawing.Size(70, 25);
            this.childLabel.TabIndex = 11;
            this.childLabel.Text = "label1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1676, 834);
            this.Controls.Add(this.childLabel);
            this.Controls.Add(this.parentLabel);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.childDataGridView);
            this.Controls.Add(this.parentDataGridView);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.childDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.DataGridView childDataGridView;
        private System.Windows.Forms.DataGridView parentDataGridView;
        private System.Windows.Forms.Label parentLabel;
        private System.Windows.Forms.Label childLabel;
    }
}

