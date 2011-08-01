
//Title:       Show Fonts Applet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description:
package showfont;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class ShowFontApplet extends Applet {
  boolean isStandalone = false;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public ShowFontApplet() {
  }

  //Initialize the applet
  public void init()
  {
    NewFrame f=new NewFrame("The ShowFonts Applet");
    MenuBar mb = new MenuBar();
    f.setMenuBar(mb);
    Menu m=new Menu("Font");
    Menu c=new Menu("Color");

    MenuItem tritem=new MenuItem("TimesRoman");
    MenuItem aitem = new MenuItem("Arial");
    MenuItem citem = new MenuItem("Courier");

    MenuItem black=new MenuItem("Black");
    MenuItem red=new MenuItem("Red");
    MenuItem green=new MenuItem("Green");

    m.add(tritem);
    m.add("-");
    m.add(aitem);
    m.add("-");
    m.add(citem);

    c.add(black);
    c.add("-");
    c.add(red);
    c.add("-");
    c.add(green);


    mb.add(m);
    mb.add(c);
    tritem.addActionListener(f);
    aitem.addActionListener(f);
    citem.addActionListener(f);
    black.addActionListener(f);
    red.addActionListener(f);
    green.addActionListener(f);
    f.setSize(800,450);
    f.show();


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

  //Get Applet information
  public String getAppletInfo() {
    return "Applet Information";
  }

  //Get parameter info
  public String[][] getParameterInfo() {
    return null;
  }
}