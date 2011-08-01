
//Title:       Text Area Applet
//Version:     1.0
//Copyright:   Copyright (c)
//Author:      Jesse Gumm
//Company:
//Description:
package textareaapplet;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class TextAreaApplet extends Applet {
  boolean isStandalone = false;
  TextArea textarea,textarea2;
  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public TextAreaApplet() {
  }

  //Initialize the applet
  public void init()
  {
    String s="This is an example of a\n";
    s+="textarea control, which is similar\n";
    s+="textfield, except there are multilines\n";
    s+="line4\n";
    s+="line5\n";
    s+="line6\n";
    String n = "Blah blah blah\nBlahBlahbBlah\nfghdfhdfjvteyjv\nrethvcerhvn\nerynectyncv";
    textarea = new TextArea(s,6,30);
    textarea2=new TextArea(n,6,30);
    add(textarea);
    add(textarea2);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  //Component initialization
  private void jbInit() throws Exception {
  }

  //Start the applet
  public void start() {
    textarea.setForeground(Color.blue);
    textarea2.setForeground(Color.green);
  }

  //Stop the applet
  public void stop() {
  }

  //Destroy the applet
  public void destroy() {
  }

  //Get Applet information
  public String getAppletInfo() {
    return "Applet Information";
  }

  //Get parameter info
  public String[][] getParameterInfo() {
    return null;
  }
}