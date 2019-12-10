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
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class UserControl1 : UserControl
    {
        public UserControl1()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string newTabPageLayout = Helper.LoadResourceFile("MyWpfBrowser.NewHomepage.xml");
            Tangram.UpdateNewTabPageLayout(newTabPageLayout);
            ChromeWebBrowser wb = Tangram.GetHostBrowser(this);
            if (wb != null)
            {
                wb.OpenURL("chrome://newtab", Disposition.NEW_FOREGROUND_TAB, "", "");
            }
        }
    }
}
