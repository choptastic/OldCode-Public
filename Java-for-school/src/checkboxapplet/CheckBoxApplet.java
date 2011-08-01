
//Title:
//Version:     1.0
//Copyright:   Copyright (c)
//Author:
//Company:
//Description:
package checkboxapplet;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class CheckBoxApplet extends Applet implements ItemListener{
  boolean isStandalone = false;
  // on ce again, implementing with an array rather than hardcoded
  Checkbox []checkbox =new Checkbox[3];

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public CheckBoxApplet() {
  }

  //Initialize the applet
  public void init()
  {
    checkbox[0]=new Checkbox("Option 1",null,false);
    checkbox[1]=new Checkbox("Option 2",null,false);
    checkbox[2]=new Checkbox("Option 3",null,true);
    for(int i=0;i<3;i++)
    {
      add(checkbox[i]);
      checkbox[i].addItemListener(this);
    }
    setBackground(Color.green);

    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  public void paint(Graphics g)
  {
    Font font=g.getFont();
    FontMetrics fontMetrics=g.getFontMetrics(font);
    int height=fontMetrics.getHeight();
    String str="";
    // loop to get information
    // everyhing gets appended to 'str' to be displayed after loop
    for(int i=0;i<3;i++)
    {
      str+="Opt " + String.valueOf(i+1);
      if(checkbox[i].getState()==true)
        str += " selected; ";
      else
        str += " not selected; ";
    }
    // display info
    g.drawString(str,10,120);
  }


  public void itemStateChanged(ItemEvent e)
  {
    // get info on checked box
    Checkbox c=(Checkbox) e.getSource();
    // if already checked, do not uncheck
    if(c.getState()==false)
      c.setState(true);
    // else, check empty box and uncheck the rest
    else
    {
      String str = c.getLabel();
      int selected=(int)str.charAt(str.length()-1)-49;
      for(int i=0;i<3;i++)
        if(i!=selected)
          checkbox[i].setState(false);
    }

    repaint();
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