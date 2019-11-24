﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TangramCLR;

namespace MyCSharpBrowser
{
    public partial class Form_Homepage : Form
    {
        public Form_Homepage()
        {
            InitializeComponent();
        }

        private void btnLeftRight_Click(object sender, EventArgs e)
        {
            ChromeWebBrowser wb = Tangram.ActiveBrowser();
            if (wb != null)
            {
                wb.OpenURL("http://127.0.0.1:8080/leftright.html", Disposition.NEW_FOREGROUND_TAB, "", "");
            }
        }

        private void btnGrid_Click(object sender, EventArgs e)
        {
            ChromeWebBrowser wb = Tangram.ActiveBrowser();
            if (wb != null)
            {
                wb.OpenURL("http://127.0.0.1:8080/grid.html", Disposition.NEW_FOREGROUND_TAB, "", "");
            }
        }

        private void btnFull_Click(object sender, EventArgs e)
        {
            ChromeWebBrowser wb = Tangram.ActiveBrowser();
            if (wb != null)
            {
                wb.OpenURL("http://127.0.0.1:8080/full.html", Disposition.NEW_FOREGROUND_TAB, "", "");
            }
        }
    }
}
