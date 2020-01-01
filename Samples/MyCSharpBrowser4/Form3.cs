using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using TangramCLR;
using RefObject;

namespace MyCSharpBrowser
{
    public partial class Form3 : Form
    {
        public WndNode thisNode;
        public Form3()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            WndNode leftNode = thisNode.ParentNode.GetNode(0, 0);
            RefObject.RefObject obj = leftNode.GetXObject();
            RefObjectParams inParams = new RefObjectParams();
            inParams.AddParam("from form3");
            obj.Invoke("Temp", inParams);
        }

        private void Form3_Load(object sender, EventArgs e)
        {
            thisNode = Tangram.CreatingNode;
        }
    }
}
