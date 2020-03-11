/********************************************************************************
*					Tangram Wizard - version 1.0.0							*
*********************************************************************************
* Copyright (C) 2002-2020 by Tangram Team.   All Rights Reserved.				*
*
* THIS SOURCE FILE IS THE PROPERTY OF TANGRAM TEAM AND IS NOT TO
* BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED
* WRITTEN CONSENT OF TANGRAM TEAM.
*
* THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS
* OUTLINED IN THE GPL LICENSE AGREEMENT.TANGRAM TEAM
* GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE
* THIS SOFTWARE ON A SINGLE COMPUTER.
*
* CONTACT INFORMATION:
* mailto:tangramteam@outlook.com
* https://www.tangram.dev
*
*
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using TangramCLR;

namespace TangramWinApp1
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
            if (Tangram.BuiltInBrowserModel == true)
                return;
            string newTabPageLayout = Helper.LoadResourceFile("TangramWinApp1.Default.xml");
            Tangram.UpdateNewTabPageLayout(newTabPageLayout);
            Tangram.WizData = "TangramWinApp1.wizxml";
            Tangram.OnBindCLRObjToWebPage += Tangram_OnBindCLRObjToWebPage;

            //Support Application Type:
            //Application is a Chromium Based WebBrowser
            //Tangram.AppType = TangramAppType.APP_BROWSER;

            //Application is a Chromium Based Desktop Application
            //Tangram.AppType = TangramAppType.APP_BROWSERAPP;

            //Application is a Chromium-Eclipse Based Desktop Application, Need Eclipse Binary Component and 64bit JVM
            //Tangram.AppType = TangramAppType.APP_BROWSER_ECLIPSE; 
            //Application is a Customized Eclipse IDE, Need Eclipse Binary Component and 64bit JVM
            //Tangram.AppType = TangramAppType.APP_ECLIPSE;
            //Application is a Win32 Desktop App
            //Tangram.AppType = TangramAppType.APP_WIN32;

            switch (Tangram.AppType)
            {
                case TangramAppType.APP_BROWSER:
                case TangramAppType.APP_BROWSERAPP:
                    break;
                case TangramAppType.APP_BROWSER_ECLIPSE:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();

                        Tangram.Context.MainForm.Show();
                    }
                    break;
                case TangramAppType.APP_ECLIPSE:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();
                        Tangram.Context.MainForm.Show();
                    }
                    break;
                case TangramAppType.APP_WIN32:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();

                        Tangram.Context.MainForm.Show();
                    }
                    break;
                default:
                    {
                        Tangram.MainForm = Tangram.Context.MainForm = new TangramWinApp1MDIForm();

                        Tangram.Context.MainForm.Show();
                    }
                    break;
            }

            Application.Run(Tangram.Context);
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
                if(e.Node.Tag!=null)
                {
                    string strTag = e.Node.Tag.ToString();
                    XmlDocument xml = new XmlDocument();
                    xml.LoadXml(strTag);
                    foreach( XmlAttribute attribute in xml.ChildNodes[0].Attributes)
                    {
                        thisSession.InsertString(attribute.Name, attribute.Value);
                    }
                }
                TreeView treeview = sender as TreeView;
                thisSession.InsertString("msgID", "FIRE_EVENT");
                thisSession.InsertInt64("subobjhandle", treeview.Handle.ToInt64());
                thisSession.InsertString("currentevent", "OnAfterSelect@"+ treeview.Name);
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
                thisSession.InsertString("currentevent", "OnClick@"+thisBtn.Name);
                thisSession.SendMessage();
            }
        }

        private static void ThisForm_SizeChanged(object sender, EventArgs e)
        {
            TangramSession thisSession = null;
            if(TangramCLR.Tangram.WebBindEventDic.TryGetValue(sender, out thisSession))
            {
                Form xform = sender as Form;
                thisSession.InsertString("msgID", "FIRE_EVENT");
                thisSession.InsertString("currentevent", "SizeChanged");
                thisSession.InsertString("currentsubobj", "SizeChanged");
                thisSession.InsertLong("width",xform.Width);
                thisSession.InsertLong("height",xform.Height);
                thisSession.SendMessage();
            }
        }
    }
}
