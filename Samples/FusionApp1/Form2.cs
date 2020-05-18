using RefObject;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FusionApp1
{
    public partial class Form2 : Form, IRefObjectInvokeExtension
    {
        public Form2()
        {
            InitializeComponent();
        }

        public void Invoke(string method, RefObjectParams pParams)
        {
            if (method.Equals("__SET_ATTRIBUTE__") && pParams.Count() == 2)
            {
                String attrName = pParams.GetParam(0);
                String newValue = pParams.GetParam(1);
                if (attrName.Equals("title"))
                {
                    this.Text = newValue;
                }
                else if (attrName.Equals("width"))
                {
                    int width = 0;
                    if (Int32.TryParse(newValue, out width))
                    {
                        this.Width = width;
                    }
                }
                else if (attrName.Equals("height"))
                {
                    int height = 0;
                    if (Int32.TryParse(newValue, out height))
                    {
                        this.Height = height;
                    }
                }
            }
        }
    }
}
