using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1_2
{
    public partial class Form2 : Form
    {
        private SqlDataAdapter masterTableAdapter;
        private SqlDataAdapter slaveTableAdapter;

        public Form2()
        {
            InitializeComponent();
            masterTableAdapter = new SqlDataAdapter();
            slaveTableAdapter = new SqlDataAdapter();

            var scenario = ConfigurationManager.AppSettings["scenario"];
            var master_table_key = scenario == "1" ? "scenario_one_master_table" : "scenario_two_master_table";
            var slave_table_key = scenario == "1" ? "scenario_one_slave_table" : "scenario_two_slave_table";

            var master_table = ConfigurationManager.AppSettings[master_table_key];
            var slave_table = ConfigurationManager.AppSettings[slave_table_key];
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
