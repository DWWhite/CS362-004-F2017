/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

	private boolean printStatus = false;
	private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

	public UrlValidatorTest(String testName) {
		super(testName);
	}



	public void testManualTest()
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		int errorCount=0;
		System.out.println("Testing valid URLS");

		String validURL[] = {
			"https://www.amazon.com",				//test schemes
			"https://amazon.com",
			"http://amazon.com",
			"ftp://speedtest.tele2.net/",
			"http://locallhost.com/",				//test hosts
			"http://oregonstate.edu/",
			"http://202.58.181.161/",
			"https://11.255.255.255",
			"https://amazon.com:443",				//test ports
			"https://www.google.com:80",
			"http://oregonstate.edu/about",		//test path
			"https://commons.apache.org/proper/commons-validator/apidocs/org/apache/commons/validator/routines/UrlValidator.html",
			"https://www.amazon.com/ref=nav_logo",  //test query
			"https://www.amazon.com/Black-Friday/b?ie=UTF8&node=384082011",
			"https://smile.amazon.com/s/ref=nb_sb_noss_2?url=search-alias%3Daps&field-keywords=java",
			"http://search.oregonstate.edu/?q=computer+science&close=default_frontend",
			"http://my.webpage.com/path/to/location?query=yes"
		};

		for(int i=0;i<validURL.length;i++) {
			String testURL = validURL[i];
			if(!(urlVal.isValid(testURL))) {
				System.out.println("--Expected Valid: "+testURL+"  *** Test reported invalid");
				errorCount++;
			}
		}

		System.out.println("\nTesting invalid URLS");

		String invalidURL[] = {
			"abc://google.com",				//test scheme
			"http:google.com",
			"http:/google.com",
			"ftp.my.ftp.com",
			"http://",						//test host
			"http://,",
			"http://.com",
			"http://com",
			"http://google.com:-1",			//test port
			"http://google.com:65536",
			"http://1000.255.255.255",		//test ip address
			"http://-1.-1.-1.-1",
			"http://10.222.222.222",
			"http://192.168.0.0",
			"http://172.16.0.0",
			"http://172.31.255.255",
			"http://256.256.256.256",
			"http://google.com/?.html",			//test path
			"http://google.com/index.html?param", //test query string
			"http://google.com/index.html?=",
			"http://google.com/index.html?query1=ans1?query2=ans2",
			"http://google.com/index.html?query1=ans1&",
			"http://google/com/index.html?query1=ans1=ans2",
			"word"

		};

		for(int i=0;i<invalidURL.length;i++) {
			String testURL = invalidURL[i];
			if(urlVal.isValid(testURL)) {
				System.out.println("--Expected Invalid: "+testURL+"  ***Test reported valid");
				errorCount++;
			}
		}
		int testsRun= (invalidURL.length)+(validURL.length);
		System.out.println("\n\nErrors: "+errorCount+" out of "+testsRun+" tests caused errors.");

	}

	//test the scheme
	public void testYourFirstPartition()
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String testURL;
		Boolean testValid, returnedVal;
		System.out.println("Testing schemes");

		for(int i=0;i<testScheme.length;i++) {
			testURL = testScheme[i].item + "www.amazon.com";
			testValid = testScheme[i].valid;
			returnedVal = urlVal.isValid(testURL);
			if(testValid != returnedVal ) {
				System.out.println("--Expected: "+ testValid+ " \t" +testURL+"\t  *** Test reported: "+returnedVal);
			}
		}

	}


	//test host
	public void testYourSecondPartition(){
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String testURL;
		Boolean testValid, returnedVal;
		System.out.println("Testing host");

		for(int i=0;i<testHost.length;i++) {
			testURL = "http://" + testHost[i].item;
			testValid = testHost[i].valid;
			returnedVal=urlVal.isValid(testURL);
			if(testValid!= returnedVal) {
				System.out.println("--Expected: "+ testValid+ " \t" +testURL+"\t  *** Test reported: "+returnedVal);
			}
		}
	}

	//test ports
	public void testYourThirdPartition(){
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String testURL;
		Boolean testValid, returnedVal;
		System.out.println("Testing ports");

		for(int i=0;i<testScheme.length;i++) {
			testURL = "http://www.amazon.com" + testPort[i].item;
			testValid = testPort[i].valid;
			returnedVal = urlVal.isValid(testURL);
			if(testValid != returnedVal) {
				System.out.println("--Expected: "+ testValid + " \t" +testURL+"\t  *** Test reported: "+returnedVal);
			}
		}
	}

	//test path
	public void testYourFourthPartition(){
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String testURL;
		Boolean testValid, returnedVal;
		System.out.println("Testing path");
		
		for(int i=0;i<testPath.length;i++) {
			testURL = "http://www.amazon.com" + testPath[i].item;
			testValid = testPath[i].valid;
			returnedVal = urlVal.isValid(testURL);
			if(testValid != returnedVal) {
				System.out.println("--Expected: "+ testValid + " \t" +testURL+"\t  *** Test reported: "+returnedVal);
		
			}
		}
	}

	//test query
	public void testYourFifthPartition(){
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String testURL;
		Boolean testValid, returnedVal;
		System.out.println("Testing query");

		for(int i=0;i<testQuery.length;i++) {
			testURL = "http://www.amazon.com/" + testQuery[i].item;
			testValid = testQuery[i].valid;
			returnedVal = urlVal.isValid(testURL);
			if(testValid != returnedVal) {
				System.out.println("--Expected: "+ testValid + " \t" +testURL+"\t  *** Test reported: "+returnedVal);
			}
		}
	}




	public void testIsValid()
	{
		int errors = 0, count = 0;
		System.out.println("\nTesting URL component combinations.");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		for(int i=0;i<testScheme.length;i++) {
			String schemeI =testScheme[i].item;
			boolean schemeV = testScheme[i].valid;

			for(int j=0;j<testHost.length;j++) {
				String hostI = testHost[j].item;
				boolean hostV = testHost[j].valid;

				for(int k=0;k<testPort.length;k++) {
					String portI = testPort[k].item;
					boolean portV = testPort[k].valid;

					for(int l=0;l<testPath.length;l++) {
						String pathI = testPath[l].item;
						boolean pathV = testPath[l].valid;

						for(int m=0;m<testQuery.length;m++) {
							count++;
							String queryI = testQuery[m].item;
							boolean queryV = testQuery[m].valid;
							boolean urlBool= schemeV & hostV & portV & pathV & queryV;
							boolean retVal=urlVal.isValid(schemeI+hostI+portI+pathI+queryI);
							if(retVal != urlBool) {
								System.out.println("Expected: "+ urlBool + "\t Actual: "+
										retVal+" \t"+schemeI+hostI+portI+pathI+queryI);
								errors++;
							}
						}
					}
				}
			}
		}
		System.out.println("Found " + errors + " errors out of " + count + " tests.");
	}

	public void testAnyOtherUnitTest()
	{

	}
	/**
	 * Create set of tests by taking the testUrlXXX arrays and
	 * running through all possible permutations of their combinations.
	 *
	 * @param testObjects Used to create a url.
	 */
	ResultPair[] testScheme = {new ResultPair("",false),
		new ResultPair("ftp://",true),
		new ResultPair("http://",true),
		new ResultPair("htps://",true),
		new ResultPair("abc://",false),
		new ResultPair("htp://",false),
		new ResultPair("http:/",false),
		new ResultPair("http:\\\\",false)
	};

	ResultPair[] testHost = {new ResultPair("www.google.com",true),
		new ResultPair("202.258.181.161",true),
		new ResultPair("",false),
		new ResultPair(".com",false),
		new ResultPair("*",false),
		new ResultPair("word",false),
		new ResultPair("0.0.0.0",true),
		new ResultPair("255.255.255.255",true),
		new ResultPair("256.256.256.256",false),
		new ResultPair("-1.-1.-1.-1",false),
		new ResultPair("1.1.1.1.1",false),
	};

	ResultPair [] testPort = {new ResultPair("",true),
		new ResultPair(":0",true),
		new ResultPair(":80",true),
		new ResultPair(":65535",true),
		new ResultPair(":65536",false),
		new ResultPair(":-1",false)
	};

	ResultPair [] testPath = {new ResultPair("",true),
		new ResultPair("/",true),
		new ResultPair("/index.html",true),
		new ResultPair("/next/page.html",true),
		new ResultPair("/about",true),
		new ResultPair("..",false),
		new ResultPair("/*.*",false),
		new ResultPair("/*.*/",false)
	};

	ResultPair [] testQuery = {new ResultPair("",true),
		new ResultPair("?q1=a1",true),
		new ResultPair("?q1=a1&q2=a2",true),
		new ResultPair("?param",false),
		new ResultPair("?=",false),
		new ResultPair("?query1=ans?query2=ans2",false),
		new ResultPair("?query1=ans1&",false),
		new ResultPair("?query1=ans1=ans2",false),
		new ResultPair("?query1=?query2=ans1",false),
		new ResultPair("?query1=&ans1",false)
	};

}



















