
//Title:        Package Applet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description:
package mypack2;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import mypack2.*;

public class mypackage extends Applet {
  boolean isStandalone = false;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public mypackage() {
  }

  //Initialize the applet
  public void init() {
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
  }

  //Stop the applet
  public void stop() {
  }

  //Destroy the applet
  public void destroy() {
  }

  public void paint(Graphics g)
  {
    Font font=new Font("TimesRoman",Font.PLAIN,24);
    g.setFont(font);
    Display3Class my3class=new Display3Class();
    String s3 = my3class.GetDisplay3Text();
    g.drawString(s3,60,80);
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