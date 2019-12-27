using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TangramCLR;

namespace MyWpfBrowser
{
    /// <summary>
    /// Interaction logic for UserControl2.xaml
    /// </summary>
    public partial class UserControl2 : UserControl
    {
        private WndNode thisNode;

        public UserControl2()
        {
            InitializeComponent();
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
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

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            thisNode.SendIPCMessage("web", "Hello Webpage!", "", "");
        }
    }
}
