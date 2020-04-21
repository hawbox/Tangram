using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using TangramCLR;

namespace ChromiumApp19
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            // Important! Don't move this line.
            Tangram.OnBindCLRObjToWebPage += Tangram_OnBindCLRObjToWebPage;
            if (Tangram.WebRuntimeInit)
            {
                return;
            }
            // We don't need to specify the main window here.
            Application.Run();
        }
        private static void Tangram_OnBindCLRObjToWebPage(object SourceObj, TangramSession eventSession, string eventName)
        {
            switch (eventName)
            {
                case "SizeChanged":
                    {
                        Form thisForm = SourceObj as Form;
                        thisForm.SizeChanged += ThisForm_SizeChanged;
                    }
                    break;
                case "OnClick":
                    {
                        Button thisbtn = SourceObj as Button;
                        thisbtn.Click += Thisbtn_Click;
                    }
                    break;
                case "OnAfterSelect":
                    {
                        TreeView thisTreeview = SourceObj as TreeView;
                        thisTreeview.AfterSelect += ThisTreeview_AfterSelect;
                    }
                    break;
            }
        }

        private static void ThisTreeview_AfterSelect(object sender, TreeViewEventArgs e)
        {
            TangramSession thisSession = null;
            if (TangramCLR.Tangram.WebBindEventDic.TryGetValue(sender, out thisSession))
            {
                if (e.Node.Tag != null)
                {
                    string strTag = e.Node.Tag.ToString();
                    XmlDocument xml = new XmlDocument();
                    xml.LoadXml(strTag);
                    foreach (XmlAttribute attribute in xml.ChildNodes[0].Attributes)
                    {
                        thisSession.InsertString(attribute.Name, attribute.Value);
                    }
                }
                TreeView treeview = sender as TreeView;
                thisSession.InsertString("msgID", "FIRE_EVENT");
                thisSession.InsertInt64("subobjhandle", treeview.Handle.ToInt64());
                thisSession.InsertString("currentevent", "OnAfterSelect@" + treeview.Name);
                thisSession.InsertString("currentsubobj", treeview.Name);
                thisSession.SendMessage();
            }
        }

        private static void Thisbtn_Click(object sender, EventArgs e)
        {
            TangramSession thisSession = null;
            if (TangramCLR.Tangram.WebBindEventDic.TryGetValue(sender, out thisSession))
            {
                Button thisBtn = sender as Button;
                thisSession.InsertString("msgID", "FIRE_EVENT");
                thisSession.InsertString("currentsubobj", thisBtn.Name);
                thisSession.InsertString("currentevent", "OnClick@" + thisBtn.Name);
                thisSession.SendMessage();
            }
        }

        private static void ThisForm_SizeChanged(object sender, EventArgs e)
        {
            TangramSession thisSession = null;
            if (TangramCLR.Tangram.WebBindEventDic.TryGetValue(sender, out thisSession))
            {
                Form xform = sender as Form;
                thisSession.InsertString("msgID", "FIRE_EVENT");
                thisSession.InsertString("currentevent", "SizeChanged");
                thisSession.InsertString("currentsubobj", "SizeChanged");
                thisSession.InsertLong("width", xform.Width);
                thisSession.InsertLong("height", xform.Height);
                thisSession.SendMessage();
            }
        }
    }
}
