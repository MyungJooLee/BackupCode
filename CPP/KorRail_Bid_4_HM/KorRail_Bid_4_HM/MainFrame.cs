using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Threading;
using System.Collections.Specialized;

namespace KorRail_Bid_4_HM
{
    public partial class MainFrame : Form
    {
        bool bRun = false;
        HttpWebRequest req;
        HttpWebResponse rep;
        Thread JobThread;


        public MainFrame()
        {
            
            InitializeComponent();
            Timer1.Start();
        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            TimeLabel.Text = DateTime.Now.ToLongTimeString();
        }

        private void LoginProcess()
        {
            string response;
            TextReader r;
            /*
            document.form2.UserId .value     = document.form1.txtMemberNo.value;
	        document.form2.UserPwd.value     = document.form1.txtPwd     .value;
	        document.form2.selInputFlg.value = document.form1.selInputFlg.value;

	        document.form2.action = pub3+'/servlets/hc.hc14100.sw_hc14111_i2Svt';
	        document.form2.submit();
             */
            //

            using (WebClient client = new WebClient())
            {       
                req = (HttpWebRequest)WebRequest.Create("https://www.korail.com/servlets/hc.hc14100.sw_hc14111_i2Svt");
                string postData = "UserId=" + IDTextBox.Text + "&UserPwd=" + PWTextBox.Text + "&selInputFlg=2";
                //byte[] sendData = UTF8Encoding.UTF8.GetBytes(postData);   
                byte[] sendData = Encoding.GetEncoding("EUC-KR").GetBytes(postData);
                
                //WebRequest.ContentType = "application/x-www-form-urlencoded; charset=UTF-8";
                req.ContentType = "application/x-www-form-urlencoded; charset=euc-kr;";
                //req.ContentType = "application/x-www-form-urlencoded; charset=utf-8";
                req.Method = "POST";

                req.ContentLength = sendData.Length;
                
                
                Stream requestStream = req.GetRequestStream();
                requestStream.Write(sendData, 0, sendData.Length);
                requestStream.Close();
                rep = (HttpWebResponse)req.GetResponse();
                StreamReader streamReader = new StreamReader(rep.GetResponseStream(), Encoding.GetEncoding("EUC-KR"));    // Encoding.GetEncoding("EUC-KR")
                string html = streamReader.ReadToEnd();
                streamReader.Close();
                //rep.Close();


                Browser.DocumentText = html;
                //r = (TextReader)new StreamReader(rep.GetResponseStream(), Encoding.Default);
                //..... 

                // 인코딩 1 - UTF-8

    
            }
        }
        private void SearchProcess()
        {

        }
        private void ReservationProcess()
        {

        }

        private void RealJob()
        {
            string response;
            TextReader r;

            int conti = 0;
            int index = 1;

            //MessageBox.Show("Test");
            while (true)
            {
                // 1. 로그인
                LoginProcess();

                // 2. 원하는 열차 검색


                // 3. 예약


                // 4. 결제화면 뿌리기

                break;



                ///////////////////////////////////////// 참고용//////////////////////////////////////////////////
                //로그인
                /*
               string response;
               using (WebClient client = new WebClient())
               {
                   NameValueCollection col = new NameValueCollection();
                   col.Add("stdNo", "학법");
                   col.Add("passwd", "비번");

                   byte[] byteResponse = client.UploadValues("http://su.kau.ac.kr/sugang/Login", col);
                   response = Encoding.Default.GetString(byteResponse);

                   //..... 
               }
               */


                //label1.Text = index.ToString();
                /*
                // 로그인(사용자 인증)후에 할 일.
                //req = (HttpWebRequest)WebRequest.Create("http://su.kau.ac.kr/sugang/SugangApply?cmd=apply&gwamokNo=0016&gwamokNm=미디어와콘텐츠&isu=30");
                //if(index % 4 == 0)
                //    req = (HttpWebRequest)WebRequest.Create("http://su.kau.ac.kr/sugang/SugangCulList.jsp?selectCd=01012&selectCd1=" + (index % 4 + 1));
                //else
                    req = (HttpWebRequest)WebRequest.Create("http://su.kau.ac.kr/sugang/SugangCulList.jsp?selectCd=01011&selectCd1="+ (index%4 +1));
                
                 // 세션 쿠키의 유지                 
                req.CookieContainer = new CookieContainer();
                req.CookieContainer.Add(rep.Cookies);
                rep = (HttpWebResponse)req.GetResponse();
                r = (TextReader)new StreamReader(rep.GetResponseStream(), Encoding.Default);
                response = r.ReadToEnd();
                int a = response.IndexOf("<font color=red>초과</font>");
                if (a > 0)
                {
                    a = response.IndexOf("<font color=red>초과</font>");
                    if (a < 0)
                    {
                        conti = 1;
                    }
                }
                else
                {

                }
                */
                conti = 1;

                //if (conti == 1)
                {
                    /*if(index % 4 == 0)
                    {
                        button2_Click(null, null);
                        req = (HttpWebRequest)WebRequest.Create("http://su.kau.ac.kr/sugang/SugangApply?cmd=apply&gwamokNo=0185&gwamokNm=미디어와콘텐츠&isu=30");
                        // 세션 쿠키의 유지
                        req.CookieContainer = new CookieContainer();
                        req.CookieContainer.Add(rep.Cookies);
                        rep = (HttpWebResponse)req.GetResponse();
                        r = (TextReader)new StreamReader(rep.GetResponseStream(), Encoding.Default);
                        r.ReadToEnd();
                    }
                    else
                     */
                    {

                        req = (HttpWebRequest)WebRequest.Create("http://su.kau.ac.kr/sugang/SugangApply?cmd=apply&gwamokNo=0694&gwamokNm=대학생이 꼭 알아야 할 회계상식&isu=30");
                        // 세션 쿠키의 유지
                        req.CookieContainer = new CookieContainer();
                        req.CookieContainer.Add(rep.Cookies);
                        rep = (HttpWebResponse)req.GetResponse();
                        r = (TextReader)new StreamReader(rep.GetResponseStream(), Encoding.Default);
                        r.ReadToEnd();
                        //string result = r.ReadToEnd();
                        //MessageBox.Show(result);


                        req = (HttpWebRequest)WebRequest.Create("http://su.kau.ac.kr/sugang/SugangApply?cmd=apply&gwamokNo=0693&gwamokNm=헤르만헤세의 시문화 산책&isu=30");
                        // 세션 쿠키의 유지
                        req.CookieContainer = new CookieContainer();
                        req.CookieContainer.Add(rep.Cookies);
                        rep = (HttpWebResponse)req.GetResponse();
                        r = (TextReader)new StreamReader(rep.GetResponseStream(), Encoding.Default);
                        r.ReadToEnd();
                        //result = r.ReadToEnd();
                        //MessageBox.Show(result);


                        req = (HttpWebRequest)WebRequest.Create("http://su.kau.ac.kr/sugang/SugangApply?cmd=apply&gwamokNo=0693&gwamokNm=헤르만헤세의 시문화 산책&isu=30");
                        // 세션 쿠키의 유지
                        req.CookieContainer = new CookieContainer();
                        req.CookieContainer.Add(rep.Cookies);
                        rep = (HttpWebResponse)req.GetResponse();
                        r = (TextReader)new StreamReader(rep.GetResponseStream(), Encoding.Default);
                        r.ReadToEnd();
                        //result = r.ReadToEnd();
                        //MessageBox.Show(result);
                    }
                }


                Thread.Sleep(1000);


                // break;
            }

        }
        private void StartButton_Click(object sender, EventArgs e)
        {
            if (bRun == false)
            {   // Stop -> Start Status
                JobThread = new Thread(new ThreadStart(this.RealJob));
                JobThread.Start();

                bRun = true;
                StartButton.Text = "Stop";
            }
            else
            {
                // Stop -> Start Status
                JobThread.Abort();

                bRun = false;
                StartButton.Text = "Start";
            }
        }
    }
}
