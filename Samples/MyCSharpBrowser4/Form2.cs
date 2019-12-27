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

namespace MyCSharpBrowser
{
    public partial class Form2 : Form
    {
        private WndNode thisNode;

        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            thisNode = Tangram.CreatingNode;
            thisNode.AddChannel("csharp");
            thisNode.OnIPCMessageReceived += ThisNode_OnIPCMessageReceived;
        }

        private void ThisNode_OnIPCMessageReceived(string strFrom, string strTo, string strMsgId, string strPayload, string strExtra)
        {
            if (strTo.Equals("csharp"))
            {
                MessageBox.Show(strPayload);
            }
        }

        private void btnHelloWebPage_Click(object sender, EventArgs e)
        {
            String msgId = thisNode.SendIPCMessage("web", "Hello Webpage!", "", "");
        }
    }
}
