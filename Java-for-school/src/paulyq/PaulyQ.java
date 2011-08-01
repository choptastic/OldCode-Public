
//Title:       PaulyQ Applet
//Version:     1.0
//Copyright:   Copyright (c)
//Author:      Jesse Gumm
//Company:
//Description:
package paulyq;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class PaulyQ extends Applet {
  boolean isStandalone = false;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public PaulyQ() {
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

  public void paint(Graphics g)
  {
    Font f = new Font("Times New Roman",Font.PLAIN,20);
    g.setFont(f);
    g.drawRoundRect(75,20,150,75,20,20);
    g.drawString("Don't Quote Me!",85,60);
    g.drawLine(120,150,175,95);
    g.drawOval(70,115,45,45);
    g.fillRoundRect(80,125,8,15,7,10);
    g.fillRoundRect(95,123,8,15,7,10);
    g.drawArc(80,140,22,15,340,235);  // heres the only modification
                                      // start drawing at 340
                                      // draw 235 degrees
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

  //Get Applet information
  public String getAppletInfo() {
    return "Applet Information";
  }

  //Get parameter info
  public String[][] getParameterInfo() {
    return null;
  }
}