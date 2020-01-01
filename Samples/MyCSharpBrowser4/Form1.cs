using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TangramCLR;
using RefObject;

namespace MyCSharpBrowser
{
    public partial class Form1 : Form, ICLRRefObjectCallback
    {
        private WndNode thisNode;
        public Form1()
        {
            InitializeComponent();
        }

        public void Temp(String param1)
        {
            MessageBox.Show(param1);
        }

        private void btnNewTabPageStyle1_Click(object sender, EventArgs e)
        {
            string newTabPageLayout = Helper.LoadResourceFile("MyCSharpBrowser.Style1.xml");
            Tangram.UpdateNewTabPageLayout(newTabPageLayout);
            ChromeWebBrowser wb = Tangram.GetHostBrowser(this);
            if (wb != null)
            {
                wb.OpenURL("chrome://newtab", Disposition.NEW_FOREGROUND_TAB, "", "");
            }
        }

        private void btnNewTabPageStyle2_Click(object sender, EventArgs e)
        {
            string newTabPageLayout = Helper.LoadResourceFile("MyCSharpBrowser.Style2.xml");
            Tangram.UpdateNewTabPageLayout(newTabPageLayout);
            ChromeWebBrowser wb = Tangram.GetHostBrowser(this);
            if (wb != null)
            {
                wb.OpenURL("chrome://newtab", Disposition.NEW_FOREGROUND_TAB, "", "");
            }
        }

        private void btnNewTabPageStyle3_Click(object sender, EventArgs e)
        {
            string newTabPageLayout = Helper.LoadResourceFile("MyCSharpBrowser.Style3.xml");
            Tangram.UpdateNewTabPageLayout(newTabPageLayout);
            ChromeWebBrowser wb = Tangram.GetHostBrowser(this);
            if (wb != null)
            {
                wb.OpenURL("chrome://newtab", Disposition.NEW_FOREGROUND_TAB, "", "");
            }
        }

        private void btnHybridWebPage_Click(object sender, EventArgs e)
        {
            //ChromeWebBrowser wb = Tangram.GetHostBrowser(this);
            //if (wb != null)
            //{
            //    wb.OpenURL("https://demo.tangram.dev/homepage.html", Disposition.NEW_FOREGROUND_TAB, "", "");
            //}
            //String msgId = thisNode.SendIPCMessage("system", "colors-menu", "__getElementById__", "");
            RefObject.RefObject obj = thisNode.HostNode.GetXObject();
            RefObjectParams inParams = new RefObjectParams();
            inParams.AddParam("colors-menu");
            obj.Invoke("getElementById", inParams, this);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            thisNode = Tangram.CreatingNode;
            thisNode.AddChannel("system");
            thisNode.OnIPCMessageReceived += ThisNode_OnIPCMessageReceived;
        }

        private void ThisNode_OnIPCMessageReceived(string strFrom, string strTo, string strMsgId, string strPayload, string strExtra)
        {
            MessageBox.Show(strPayload);
        }

        public void Invoke(RefObject.RefObject obj, RefObjectParams inParams)
        {
            MessageBox.Show(inParams.GetParam(0));
        }
    }
}
