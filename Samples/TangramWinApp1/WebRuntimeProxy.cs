using System;
using System.Xml;
using TangramCLR;
using System.Windows.Forms;

namespace WebRuntimeProxy
{
    static class WebDelegate
    {
        public static int Tangram_OnAppInit(string e)
        {
            Tangram.OnBindCLRObjToWebPage += Tangram_OnBindCLRObjToWebPage;
            Tangram.OnGetSubObjForWebPage += Tangram_OnGetSubObjForWebPage;
            Tangram.OnTangramIPCMsg += Tangram_OnTangramIPCMsg;
            Tangram.OnTangramRenderHTMLElement += Tangram_OnTangramRenderHTMLElement;
            return 0;
        }

        private static object Tangram_OnGetSubObjForWebPage(object SourceObj, string subObjName)
        {
            return null;
        }

        private static void Tangram_OnTangramIPCMsg(IntPtr hWnd, string strType, string strParam1, string strParam2)
        {
        }

        private static void Tangram_OnTangramRenderHTMLElement(IntPtr hWnd, string strRuleName, string strHTML)
        {
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
                Control ctrl = sender as Control;
                if (ctrl != null && ctrl.Tag != null)
                {
                    string strTag = ctrl.Tag.ToString();
                    XmlDocument xml = new XmlDocument();
                    xml.LoadXml(strTag);
                    foreach (XmlAttribute attribute in xml.ChildNodes[0].Attributes)
                    {
                        thisSession.InsertString(attribute.Name, attribute.Value);
                    }
                }
                thisSession.SendMessage();
            }
        }

        private static void Thisbtn_Click(object sender, EventArgs e)
        {
            TangramSession thisSession = null;
            if (TangramCLR.Tangram.WebBindEventDic.TryGetValue(sender, out thisSession))
            {
                Control ctrl = sender as Control;
                thisSession.InsertString("msgID", "FIRE_EVENT");
                thisSession.InsertString("currentsubobj", ctrl.Name);
                thisSession.InsertString("currentevent", "OnClick@" + ctrl.Name);
                if (ctrl != null && ctrl.Tag != null)
                {
                    string strTag = ctrl.Tag.ToString();
                    XmlDocument xml = new XmlDocument();
                    xml.LoadXml(strTag);
                    foreach (XmlAttribute attribute in xml.ChildNodes[0].Attributes)
                    {
                        thisSession.InsertString(attribute.Name, attribute.Value);
                    }
                }
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
