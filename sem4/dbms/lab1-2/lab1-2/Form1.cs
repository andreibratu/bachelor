using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace lab1_2
{
    public partial class Form1 : Form
    {
        private string scenario;
        private string masterTableName;
        private string slaveTableName;
        private string slaveQuery;
        private string slaveParam;
        private string connectionString;

        public Form1()
        {
            setUpScenario();

            InitializeComponent();

            this.usersTableAdapter.Fill(this.ridesharingDataSet1.Users);
            this.vehiclesTableAdapter.Fill(this.ridesharingDataSet1.Vehicles);
            this.menusTableAdapter.Fill(this.ridesharingDataSet1.Menus);
            this.restaurantsTableAdapter.Fill(this.ridesharingDataSet1.Restaurants);

            this.dataGridView1.DataSource = this.ridesharingDataSet1.Tables[this.masterTableName];
            this.dataGridView2.DataSource = this.ridesharingDataSet1.Tables[this.slaveTableName];
        }

        private void setUpScenario()
        {
            this.connectionString = ConfigurationManager.AppSettings["connection"];
            this.scenario = ConfigurationManager.AppSettings["scenario"];

            string master_key = scenario == "1" ? "scenario_one_master_table" : "scenario_two_master_table";
            string slave_key = scenario == "1" ? "scenario_one_slave_table" : "scenario_two_slave_table";

            this.masterTableName = ConfigurationManager.AppSettings[master_key];
            this.slaveTableName = ConfigurationManager.AppSettings[slave_key];

            string paramKey = scenario == "1" ? "scenario_one_param_name" : "scenario_two_param_name";
            string queryKey = scenario == "1" ? "scenario_one_query" : "scenario_two_query";

            this.slaveParam = ConfigurationManager.AppSettings[paramKey];
            this.slaveQuery = ConfigurationManager.AppSettings[queryKey];
        }

        private void usersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            this.Validate();
            this.usersBindingSource.EndEdit();
            this.tableAdapterManager.UpdateAll(this.ridesharingDataSet);
        }

        private void DataGridView_RowHeaderMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            var row = dataGridView1.Rows[e.RowIndex];
            var isDriver = scenario == "1" ? row.Cells[4].Value : null;
            var masterId = row.Cells[0].Value.ToString();
            
            if (scenario == "1" && isDriver.Equals(false))
            {
                MessageBox.Show("Selected user is not a driver!");
                return;
            }

            SqlConnection connection;
            using (connection = new SqlConnection("Server=DESKTOP-R4AMR8A\\SQLEXPRESS;Database=ridesharing;Trusted_Connection=True"))
            {
                connection.Open();
                SqlCommand query = new SqlCommand(this.slaveQuery, connection);
                query.Parameters.Add(new SqlParameter(this.slaveParam, masterId));
                SqlDataAdapter adapter = new SqlDataAdapter(query);
                DataSet new_ds = new DataSet();
                int result = adapter.Fill(new_ds, this.slaveTableName);
                this.dataGridView2.DataSource = new_ds.Tables[this.slaveTableName];
                connection.Close();
            }
        }

        private void usersBindingSource1BindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            this.Validate();
            this.usersBindingSource1.EndEdit();
            this.tableAdapterManager1.UpdateAll(this.ridesharingDataSet1);

        }
    }
}
