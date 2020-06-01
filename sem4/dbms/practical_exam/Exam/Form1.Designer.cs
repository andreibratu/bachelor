namespace Exam
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
            this.components = new System.ComponentModel.Container();
            this.dgvCategories = new System.Windows.Forms.DataGridView();
            this.mcidDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.catnameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.catdescrDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.categoriesBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.jaleDataSet = new Exam.jaleDataSet();
            this.dgvMovies = new System.Windows.Forms.DataGridView();
            this.midDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.titleDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.pidDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.mcidDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.moviesBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.moviesTableAdapter = new Exam.jaleDataSetTableAdapters.MoviesTableAdapter();
            this.categoriesTableAdapter = new Exam.jaleDataSetTableAdapters.CategoriesTableAdapter();
            this.commitButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvCategories)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.categoriesBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.jaleDataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvMovies)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.moviesBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvCategories
            // 
            this.dgvCategories.AutoGenerateColumns = false;
            this.dgvCategories.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvCategories.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.mcidDataGridViewTextBoxColumn1,
            this.catnameDataGridViewTextBoxColumn,
            this.catdescrDataGridViewTextBoxColumn});
            this.dgvCategories.DataSource = this.categoriesBindingSource;
            this.dgvCategories.Location = new System.Drawing.Point(13, 13);
            this.dgvCategories.Name = "dgvCategories";
            this.dgvCategories.RowHeadersWidth = 51;
            this.dgvCategories.RowTemplate.Height = 24;
            this.dgvCategories.Size = new System.Drawing.Size(292, 299);
            this.dgvCategories.TabIndex = 0;
            this.dgvCategories.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // mcidDataGridViewTextBoxColumn1
            // 
            this.mcidDataGridViewTextBoxColumn1.DataPropertyName = "mc_id";
            this.mcidDataGridViewTextBoxColumn1.HeaderText = "mc_id";
            this.mcidDataGridViewTextBoxColumn1.MinimumWidth = 6;
            this.mcidDataGridViewTextBoxColumn1.Name = "mcidDataGridViewTextBoxColumn1";
            this.mcidDataGridViewTextBoxColumn1.Width = 125;
            // 
            // catnameDataGridViewTextBoxColumn
            // 
            this.catnameDataGridViewTextBoxColumn.DataPropertyName = "cat_name";
            this.catnameDataGridViewTextBoxColumn.HeaderText = "cat_name";
            this.catnameDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.catnameDataGridViewTextBoxColumn.Name = "catnameDataGridViewTextBoxColumn";
            this.catnameDataGridViewTextBoxColumn.Width = 125;
            // 
            // catdescrDataGridViewTextBoxColumn
            // 
            this.catdescrDataGridViewTextBoxColumn.DataPropertyName = "cat_descr";
            this.catdescrDataGridViewTextBoxColumn.HeaderText = "cat_descr";
            this.catdescrDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.catdescrDataGridViewTextBoxColumn.Name = "catdescrDataGridViewTextBoxColumn";
            this.catdescrDataGridViewTextBoxColumn.Width = 125;
            // 
            // categoriesBindingSource
            // 
            this.categoriesBindingSource.DataMember = "Categories";
            this.categoriesBindingSource.DataSource = this.jaleDataSet;
            // 
            // jaleDataSet
            // 
            this.jaleDataSet.DataSetName = "jaleDataSet";
            this.jaleDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // dgvMovies
            // 
            this.dgvMovies.AutoGenerateColumns = false;
            this.dgvMovies.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvMovies.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.midDataGridViewTextBoxColumn,
            this.titleDataGridViewTextBoxColumn,
            this.pidDataGridViewTextBoxColumn,
            this.mcidDataGridViewTextBoxColumn});
            this.dgvMovies.DataSource = this.moviesBindingSource;
            this.dgvMovies.Location = new System.Drawing.Point(422, 13);
            this.dgvMovies.Name = "dgvMovies";
            this.dgvMovies.RowHeadersWidth = 51;
            this.dgvMovies.RowTemplate.Height = 24;
            this.dgvMovies.Size = new System.Drawing.Size(333, 425);
            this.dgvMovies.TabIndex = 1;
            this.dgvMovies.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
            // 
            // midDataGridViewTextBoxColumn
            // 
            this.midDataGridViewTextBoxColumn.DataPropertyName = "m_id";
            this.midDataGridViewTextBoxColumn.HeaderText = "m_id";
            this.midDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.midDataGridViewTextBoxColumn.Name = "midDataGridViewTextBoxColumn";
            this.midDataGridViewTextBoxColumn.Width = 125;
            // 
            // titleDataGridViewTextBoxColumn
            // 
            this.titleDataGridViewTextBoxColumn.DataPropertyName = "title";
            this.titleDataGridViewTextBoxColumn.HeaderText = "title";
            this.titleDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.titleDataGridViewTextBoxColumn.Name = "titleDataGridViewTextBoxColumn";
            this.titleDataGridViewTextBoxColumn.Width = 125;
            // 
            // pidDataGridViewTextBoxColumn
            // 
            this.pidDataGridViewTextBoxColumn.DataPropertyName = "p_id";
            this.pidDataGridViewTextBoxColumn.HeaderText = "p_id";
            this.pidDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.pidDataGridViewTextBoxColumn.Name = "pidDataGridViewTextBoxColumn";
            this.pidDataGridViewTextBoxColumn.Width = 125;
            // 
            // mcidDataGridViewTextBoxColumn
            // 
            this.mcidDataGridViewTextBoxColumn.DataPropertyName = "mc_id";
            this.mcidDataGridViewTextBoxColumn.HeaderText = "mc_id";
            this.mcidDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.mcidDataGridViewTextBoxColumn.Name = "mcidDataGridViewTextBoxColumn";
            this.mcidDataGridViewTextBoxColumn.Width = 125;
            // 
            // moviesBindingSource
            // 
            this.moviesBindingSource.DataMember = "Movies";
            this.moviesBindingSource.DataSource = this.jaleDataSet;
            // 
            // moviesTableAdapter
            // 
            this.moviesTableAdapter.ClearBeforeFill = true;
            // 
            // categoriesTableAdapter
            // 
            this.categoriesTableAdapter.ClearBeforeFill = true;
            // 
            // commitButton
            // 
            this.commitButton.Location = new System.Drawing.Point(63, 360);
            this.commitButton.Name = "commitButton";
            this.commitButton.Size = new System.Drawing.Size(223, 52);
            this.commitButton.TabIndex = 2;
            this.commitButton.Text = "Commit";
            this.commitButton.UseVisualStyleBackColor = true;
            this.commitButton.Click += new System.EventHandler(this.commitButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.commitButton);
            this.Controls.Add(this.dgvMovies);
            this.Controls.Add(this.dgvCategories);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvCategories)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.categoriesBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.jaleDataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvMovies)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.moviesBindingSource)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvCategories;
        private System.Windows.Forms.DataGridView dgvMovies;
        private jaleDataSet jaleDataSet;
        private System.Windows.Forms.BindingSource moviesBindingSource;
        private jaleDataSetTableAdapters.MoviesTableAdapter moviesTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn midDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn titleDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn pidDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn mcidDataGridViewTextBoxColumn;
        private System.Windows.Forms.BindingSource categoriesBindingSource;
        private jaleDataSetTableAdapters.CategoriesTableAdapter categoriesTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn mcidDataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn catnameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn catdescrDataGridViewTextBoxColumn;
        private System.Windows.Forms.Button commitButton;
    }
}

