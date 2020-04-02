using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'ridesharingDataSet.Vehicles' table. You can move, or remove it, as needed.
            this.vehiclesTableAdapter.Fill(this.ridesharingDataSet.Vehicles);
            // TODO: This line of code loads data into the 'ridesharingDataSet.Users' table. You can move, or remove it, as needed.
            this.usersTableAdapter.Fill(this.ridesharingDataSet.Users);
        }

        private void usersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            this.Validate();
            this.usersBindingSource.EndEdit();
            this.tableAdapterManager.UpdateAll(this.ridesharingDataSet);
        }

        private void UsersDataGridView_RowHeaderMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            var row = usersDataGridView1.Rows[e.RowIndex];
            var isDriver = row.Cells[4].Value;
            var userId = row.Cells[0].Value.ToString();
            
            if (isDriver.Equals(false))
            {
                MessageBox.Show("Selected user is not a driver!");
                return;
            }

            SqlConnection connection;
            using (connection = new SqlConnection("Server=DESKTOP-R4AMR8A\\SQLEXPRESS;Database=ridesharing;Trusted_Connection=True"))
            {
                connection.Open();
                SqlCommand query = new SqlCommand("SELECT * FROM Vehicles WHERE UserId=@UserId", connection);
                query.Parameters.Add(new SqlParameter("@UserId", userId));
                SqlDataAdapter adapter = new SqlDataAdapter(query);
                DataSet vehicles = new DataSet();
                int result = adapter.Fill(vehicles, "Vehicles");
                this.vehiclesDataGridView1.DataSource = vehicles.Tables["Vehicles"];
                connection.Close();
            }
        }

        private void usersBindingSource1BindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            this.Validate();
            this.usersBindingSource1.EndEdit();
            this.tableAdapterManager1.UpdateAll(this.ridesharingDataSet1);

        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'ridesharingDataSet1.Vehicles' table. You can move, or remove it, as needed.
            this.vehiclesTableAdapter1.Fill(this.ridesharingDataSet1.Vehicles);
            // TODO: This line of code loads data into the 'ridesharingDataSet1.Users' table. You can move, or remove it, as needed.
            this.usersTableAdapter1.Fill(this.ridesharingDataSet1.Users);
        }
    }
}
