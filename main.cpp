#include <GLFW/glfw3.h>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include<string>
#include<ctime>
#include<vector>
using namespace std;
// class to generate strings.
class stream
{
private:
    string str;
    int n;
public:
    stream(int k)
    {
        n = k;
    }
    string random()
    {
        srand(time(NULL)); // used to generate different random no on program execution.
        for (int i = 0; i < n; i++)
        {
            if (rand() % 2)
                str.append("1");
            else
                str.append("0");
        }
        return str;
    }
    string fixed()
    {
        srand(time(NULL));
        int k, i;
        cout << "press\n 1: for 8 consecutive 0s\n 2: for 4 consecutive 0s...:";
        cin >> k;
        switch (k)
        {
            case 1:
                if (n > 8)
                {
                    for (i = 0; i < n - 8; i++)
                    {
                        if (rand() % 2)
                            str.append("1");
                        else
                            str.append("0");
                    }
                    str.insert(i, "00000000");
                }
                break;
            case 2:
                if (n > 4)
                {
                    for (i = 0; i < n - 4; i++)
                    {
                        if (rand() % 2)
                            str.append("1");
                        else
                            str.append("0");
                    }
                    str.insert(i, "0000");
                }
                break;
            default:
                cout << "not valid input\n";

        }
        
        
        return str;
        
    }
};
// class to generate longest common subsequence.
// dyanamic programming is used.
// lps problem is converted into lcs.
class subsequence
{
public:
    string longestCommonSubsequence(string s, string r) {
        int n = s.length(), m = r.length();
        vector<vector<int> >mat(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                char x = s[i - 1], y = r[j - 1];
                if (x == y) {
                    mat[i][j] = mat[i - 1][j - 1] + 1;
                }
                else {
                    mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
                }
            }
        }
        int rw = n, cl = m;
        string ret = "";
        while (rw > 0 && cl > 0) {
            if (s[rw - 1] == r[cl - 1]) {
                ret += s[rw - 1];
                rw--;
                cl--;
            }
            else {
                if (mat[rw - 1][cl] > mat[rw][cl - 1]) {
                    rw--;
                }
                else if (mat[rw][cl - 1] > mat[rw - 1][cl]) {
                    cl--;
                }
                else if (mat[rw][cl - 1] == mat[rw - 1][cl]) {
                    rw--;
                }
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
class encoding     // upper class
{
  private:
      string str;
      int n;
      float step;
      float x1, x2;
      // x1,x2 represent the x co-ordinate.
  public:
      encoding(string data, int k)
      {
          str = data;
          n = k;
          step = 1.8 / n;
      }
      // there is no use of return value but it is used to avoid
      // the error of pointer to void method error.
      int nrzi()
      {
          int i,up;
          // up variable to locate the side of the graph
          
          // code block for first bit
           x1 = -0.9;
           x2 = -0.9+step;
           glColor3f(0.0f, 1.0f, 0.0f);
           glBegin(GL_LINE_STRIP);
           glVertex2f(x1,0.3);
           glVertex2f(x2, 0.3);
           glEnd();
           glFlush();
           up = 1;
         // end block
           for (i = 1; i < n; i++)
           {
               // when graph is upper side (up=1)
               if (str[i] == '0' && up == 1)
               {
                   x1 = x2;
                   x2 = x1 + step;
                   glBegin(GL_LINE_STRIP);
                   glVertex2f(x1, 0.3);
                   glVertex2f(x2, 0.3);
                   glEnd();
                   glFlush();
               }
               // when graph is lower side (up=-1)
               else if (str[i] == '0' && up == -1)
               {
                   x1 = x2;
                   x2 = x1 + step;
                   glBegin(GL_LINE_STRIP);
                   glVertex2f(x1, -0.3);
                   glVertex2f(x2, -0.3);
                   glEnd();
                   glFlush();
               }
               else if (str[i] == '1' && up == 1)
               {
                   glBegin(GL_LINE_STRIP);
                   glVertex2f(x2, 0.3);
                   glVertex2f(x2, -0.3);
                   x1 = x2;
                   x2 = x1 + step;
                   glVertex2f(x1, -0.3);
                   glVertex2f(x2, -0.3);
                   up = -1;
                   glEnd();
                   glFlush();
               }
               else if (str[i] == '1' && up == -1)
               {
                   glBegin(GL_LINE_STRIP);
                   glVertex2f(x2, -0.3);
                   glVertex2f(x2, 0.3);
                   x1 = x2;
                   x2 = x1 + step;
                   glVertex2f(x1, 0.3);
                   glVertex2f(x2, 0.3);
                   up = 1;
                   glEnd();
                   glFlush();
               }   
           } 
           return 1;
      }
      int nrzl()
      {
          int i,prev,next;
          // prev will check if current str element is same as previous element.
          // next will check is current element is same as next str element.
          x1 = -0.9;
          x2 = -0.9;
          glColor3f(0.0f, 1.0f, 0.0f);
          for (i = 0; i < n; i++)
          {
              if (i<n && str[i] == str[i + 1])
                  next = 1;
              else
                  next = -1;
              if (i>0 && str[i] == str[i - 1])
                  prev = 1;
              else
                  prev = -1;
              if (str[i] == '0')
              {
                 glBegin(GL_LINE_STRIP);
                 x1 = x2;
                 x2 = x1 + step;
                 // when current is not equal to previous
                 if (prev != 1 && i!=0)
                 {
                 glVertex2f(x1, 0.0f);
                 glVertex2f(x1, -0.3f);
                 }
                      
                 glVertex2f(x1, -0.3f);
                 glVertex2f(x2, -0.3f);
                 if (next != 1 && i != n-1)
                 {
                   glVertex2f(x2, -0.3f);
                   glVertex2f(x2, 0.0f);
                 }
                 glEnd();
                  
              }
              else
              {
                  glBegin(GL_LINE_STRIP);
                  x1 = x2;
                  x2 = x1 + step;
                  if (prev != 1 && i != 0)
                  {
                      glVertex2f(x1, 0.0f);
                      glVertex2f(x1, 0.3f);
                  }

                  glVertex2f(x1, 0.3f);
                  glVertex2f(x2, 0.3f);
                  if (next != 1 && i!=n-1)
                  {
                      glVertex2f(x2, 0.3f);
                      glVertex2f(x2, 0.0f);
                  }
                  glEnd();
              }
          }
          return 1;

      }
      /*
       s_fig() and z_fig() functions are defined to use it in the manchaster and 
       differential manchaster encoding.s_fig() generate s type structure and z_fig()
       generates z type structure.
      */
      void s_fig()
      {
          glBegin(GL_LINE_STRIP);
          x1 = x2;
          x2 = x1 + step / 2;
          glVertex2f(x1, -0.3f);
          glVertex2f(x2, -0.3f);
          glVertex2f(x2, -0.3f);
          glVertex2f(x2, 0.3f);
          x1 = x2;
          x2 = x1 + step / 2;
          glVertex2f(x1, 0.3f);
          glVertex2f(x2, 0.3f);
          glEnd();
      }
      void z_fig()
      {
          glBegin(GL_LINE_STRIP);
          x1 = x2;
          x2 = x1 + step / 2;
          glVertex2f(x1, 0.3f);
          glVertex2f(x2, 0.3f);
          glVertex2f(x2, 0.3f);
          glVertex2f(x2, -0.3f);
          x1 = x2;
          x2 = x1 + step / 2;
          glVertex2f(x1, -0.3f);
          glVertex2f(x2, -0.3f);
      }
      int manchaster()
      {
          int i,flag;
          // flag is used to check whether current element is same as next or not.
          x1 = -0.9;
          x2 = -0.9;
          glColor3f(0.0f, 1.0f, 0.0f);
          for (i = 0; i < n; i++)
          {
              if (i < n && str[i] == str[i + 1])
                  flag = 1;
              else
                  flag = -1;
              if (str[i] == '0')
              {
                  z_fig();
                  glBegin(GL_LINE_STRIP);
                  if (flag == 1)
                  {
                      glVertex2f(x2, -0.3f);
                      glVertex2f(x2, +0.3f);
                  }
                  glEnd();

              }
              else
              {
                  s_fig();
                  glBegin(GL_LINE_STRIP);
                  if (flag == 1)
                  {
                      glVertex2f(x2, 0.3f);
                      glVertex2f(x2, -0.3f);
                  }
                  glEnd();
              }
          }
          return 1;
      }
      
      int diff_manchaster()
      {
          int i, up=1;
          // up is used to check whether graph is below or above x axis.
          x1 = x2 = -0.9;
          glColor3f(0.0f, 1.0f, 0.0f);
          for (i = 0; i < n; i++)
          {
              if (str[i] == '0')
              {
                  if (up == 1)
                  {
                      glBegin(GL_LINE_STRIP);
                      glVertex2f(x2, 0.3f);
                      glVertex2f(x2, -0.3f);
                      glEnd();
                      s_fig();
                      up = 1;
                  }
                  else
                  {
                      glBegin(GL_LINE_STRIP);
                      glVertex2f(x2, -0.3f);
                      glVertex2f(x2, 0.3f);
                      glEnd();
                      z_fig();
                      up = -1;
                  }
              }
              else
              {
                  if (up == -1 || i == 0)
                  {
                      s_fig();
                      up = 1;
                  }
                  else if (up == 1)
                  {
                      z_fig();
                      up = -1;
                  }
                  

              }
          }
          return 1;
      } 
      /*
      pos_square():generate positive pulse(above x-axis)
      neg_square():generate negative pulse(below x-axis)
      zero(): on x axis.
      All these functions are used in scrambled and unscrambled AMI line encoding.
      */
      void pos_square()
      {
          glBegin(GL_LINE_STRIP);
          glVertex2f(x2, 0.0f);
          glVertex2f(x2, 0.3f);
          x1 = x2;
          x2 = x1 + step;
          glVertex2f(x1, 0.3f);
          glVertex2f(x2, 0.3f);
          glVertex2f(x2, 0.3f);
          glVertex2f(x2, 0.0f);
          glEnd();
      }
      void neg_square()
      {
          glBegin(GL_LINE_STRIP);
          glVertex2f(x2, 0.0f);
          glVertex2f(x2, -0.3f);
          x1 = x2;
          x2 = x1 + step;
          glVertex2f(x1, -0.3f);
          glVertex2f(x2, -0.3f);
          glVertex2f(x2, -0.3f);
          glVertex2f(x2, 0.0f);
          glEnd();
      }
      void zero()
      {
          x1 = x2;
          x2 = x1 + step;
          glBegin(GL_LINE_STRIP);
          glVertex2f(x1, 0.0f);
          glVertex2f(x2, 0.0f);
          glEnd();
      }
      int ami()
      {
          int i, up =-1;
          // up checks whether signal is above(1) or below x-aixs
          x1 = x2 = -0.9;
          glColor3f(0.0f, 1.0f, 0.0f);
          for (i = 0; i < n; i++)
          {
              if (str[i] == '0')
              {
                  
                  zero();
              }
              else
              {
                  if (up == 1)
                  {
                      neg_square();
                      up = -1;
                  }
                  else
                  {
                      pos_square();
                      up = 1;
                  }
              }
          }
          return 1;
      }
      int hdb3()
      {
          x1 = x2 = -0.9;
          glColor3f(0.0f, 1.0f, 0.0f);
          int i = 0;
          int count_one = 1; // to check parity
          int count_strict = 0;
          while (i < n)
          {
              if (str[i] == '1')
              {
                  ++count_strict;
                  ++count_one;
                  if (!(count_one & 1)) // checking parity via bit manipulation(and operator)(even or odd)
                      pos_square();
                  else
                      neg_square();
                  ++i;
              }
              else if (str[i] == '0')
              {
                  int count_zeroes = 0;
                  int j = i;
                  int t = j + 3;
                  if (t < n)
                  {
                      while (j <= t)
                      {
                          if (str[j] == '0')
                              ++count_zeroes;
                          else
                              break;
                          ++j;
                      }
                  }
                  // scrambled logic start
                  if (count_zeroes == 4)
                  {
                      if (!(count_strict & 1))
                      {
                          count_one += 1;
                          int t = 0;
                          int p = i;
                          while (i <= p + 3)
                          {
                              if (t == 0)
                              {
                                  if (!(count_one & 1))
                                      pos_square();
                                  else
                                      neg_square();
                                  t = 1;
                                  ++i;
                              }
                              else
                              {
                                  if (t == 3)
                                  {
                                      if (!(count_one & 1))
                                          pos_square();
                                      else
                                          neg_square();
                                      ++i;
                                      ++t;
                                  }
                                  else
                                  {
                                      zero();
                                      ++t;
                                      ++i;

                                  }
                              }
                          }
                          count_strict += 2;
                      }
                      else if (count_strict & 1)
                      {
                          int t = 0;
                          int p = i;
                          while (i <= p + 3)
                          {
                              if (t == 3)
                              {
                                  if ((count_one & 1))
                                  {
                                      neg_square();
                                  }
                                  else
                                  {
                                      pos_square();
                                  }
                                  ++i;
                                  ++t;
                              }
                              else
                              {
                                  zero();
                                  ++i;
                                  ++t;
                              }
                          }
                          count_strict += 1;
                      }
                  }
                  else
                  {
                      zero();
                      ++i;
                  }
                  // scrambled logic ends.
              }
          }
          return 1;
      }
       
      int b8zs()
      {
          //000VB0VB
          x1 = x2 = -0.9;
          glColor3f(0.0f, 1.0f, 0.0f);
          int count_one = 1;
         
          int i = 0;
          while (i < n)
          {
              if (str[i] == '1')
              {
                 
                  ++count_one;
                  if (!(count_one & 1))
                      pos_square();
                  else
                      neg_square();
                  ++i;
              }
              else if (str[i] == '0')
              {
                  int count_zeroes = 0;
                  int j = i;
                  int t = j + 7;
                  if (t <n)
                  {
                      while (j <= t)
                      {
                          if (str[j] == '0')
                              ++count_zeroes;
                          else
                              break;
                          ++j;
                      }
                  }
                  if (count_zeroes == 8)
                  {
                      //here 000V starts
                      int t = 0;
                      int p = i;
                      while (i <= p + 3)
                      {
                          if (t == 3)
                          {
                              if ((count_one & 1))
                              {
                                  neg_square();
                              }
                              else
                              {
                                  pos_square();
                              }
                              ++i;
                              ++t;
                          }
                          else
                          {
                              zero();
                              ++i;
                              ++t;
                          }
                      }
                      
                      count_one += 1;
                      //now BOVB start here
                      t = 0;
                      p = i;
                      while (i <= p + 3)
                      {
                          if (t == 0)
                          {
                              if (!(count_one & 1))
                                  pos_square();
                              else
                                  neg_square();
                              t = 1;
                              ++i;
                          }
                          else
                          {
                              if (t == 2)
                              {
                                  if (!(count_one & 1))
                                      pos_square();
                                  else
                                      neg_square();
                                  ++i;
                                  ++t;


                              }
                              if (t == 3)
                              {
                                  if (!(count_one & 1))
                                      neg_square();
                                  else
                                      pos_square();
                                  ++i;
                                  ++t;
                                  ++count_one;
                              }
                              else
                              {
                                  zero();
                                  ++t;
                                  ++i;

                              }
                          }
                      }

                  }
                  else
                  {
                      zero();
                      ++i;

                  }
              }
          }
          return 1;
      }     
};
class plot : public encoding  // child class
{
private:
    int k;
    float step1;
public:
    // methods in this class are responsible for generating the graphic window.
    plot(string str, int n) :encoding(str,n)     // constructor
    {
        k = n;
        step1 = 1.8 / k;
    }
    static void error_callback(int error, const char* description)
    {
        fputs(description, stderr);
    }
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
    void screen(encoding* obj,int(encoding::*func)(void),const char* name)
    {
        GLFWwindow* window;
        glfwSetErrorCallback(error_callback);
        if (!glfwInit())
            exit(EXIT_FAILURE);
        window = glfwCreateWindow(1800, 700, name, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, key_callback);
        while (!glfwWindowShouldClose(window))
        {

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glLineWidth(3);
            glBegin(GL_LINE_STRIP);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(-0.9f, 0.5f);
            glVertex2f(-0.9f, -0.5f);
            glVertex2f(-0.9f, 0);
            glVertex2f(0.9f, 0);
            glEnd();
            glFlush();
            float x;
            x = -0.9;
            for (int i = 0; i < k; i++)
            {
               x = x + step1;
               glPointSize(10.0f);
               glColor3f(0.7f, 0.3f, 1.0f);
               glBegin(GL_POINTS);
               glVertex2f(x, 0.0);
               glEnd();
            }
            int k = (obj->*func)();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
};

int main()
{
    int n, d, e, s, a;
    cout << "******line encoding of digital data stream******\n";
    cout << "enter the size of stream to be generated: ";
    cin >> n;
    cout << "press:\n 1: for random stream generation\n 2: for fixed substream generation....:";
    cin >> d;
    string str;
    stream binarystr(n);
    switch (d)
    {
    case 1:
        str = binarystr.random();
        break;
    case 2:
        str = binarystr.fixed();
        break;
    default:
        cout << "invalid option choosen\n";
    }
    cout << "******************************\n";
    subsequence dstr;
    string lps, rstr;
    // converting lps into lcs
    rstr = str;
    reverse(rstr.begin(), rstr.end());
    lps = dstr.longestCommonSubsequence(str, rstr);
    cout << "digital stream generated: " << str << endl;
    cout << "longest palendromic subsequence:" << lps << endl;
    cout << "******************************\n";
    cout << "please select type of encoding technique:\n";
    cout << "press:\n 1: for NRZ-I\n 2: for NRZ-L\n 3: for manchaster(IEEE.8)\n 4: for diff manchaster(IEEE.8)\n 5: AMI....: ";
    cin >> e;
    plot signal(str, n);
    string st;
    const char* name;
    switch (e)
    {
    case 1:
        st = "NRZ-I line encoding";
        name = st.c_str();
        signal.screen(&signal,&encoding::nrzi,name);
        break;
    case 2:
        st = "NRZ-L line encoding";
        name = st.c_str();
        signal.screen(&signal, &encoding::nrzl,name);
        break;
    case 3:
        st = "Manchaster line encoding";
        name = st.c_str();
        signal.screen(&signal, &encoding::manchaster,name);
        break;
    case 4:
        st= "Differential Manchaster line encoding";
        name = st.c_str();
        signal.screen(&signal, &encoding::diff_manchaster,name);
        break;
    case 5:
        cout << "press:\n 1: for scrambled output\n 2: for unscrambled output....:";
        cin >> s;
        switch (s) 
        {
        case 1:
            cout << "press:\n 1: for HDB3\n 2: for B8ZS....:";
            cin >> a;
            switch (a)
            {
            case 1:
                st= "Scrambled HDB3 AMI line encoding";
                name = st.c_str();
                signal.screen(&signal, &encoding::hdb3, name);
                break;
            case 2:
                st= "Scrambled B8ZS AMI line encoding";
                name = st.c_str();
                signal.screen(&signal, &encoding::b8zs, name);
                break;
            default:
                cout << "invalid option choosen\n";
            }
            break;
        case 2:
            st= "Unscrambled AMI line encoding";
            name = st.c_str();
            signal.screen(&signal, &encoding::ami,name);
            break;
        default:
            cout << "invalid option\n";
        }
        break;
    default:
        cout << "invalid option\n";
    }
    
}
