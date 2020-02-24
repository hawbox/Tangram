using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TangramWinApp1
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void tabControl1_VisibleChanged(object sender, EventArgs e)
        {
            //if (tabControl1.Visible == true)
            //    htmlclient.Visible = false;
            //else
            //    htmlclient.Visible = true;
        }
    }
}
