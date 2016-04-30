package account.controllertest;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import account.controllertest.*;
import account.modelstest.*;

import java.io.IOException;
import java.util.*;

import javax.servlet.ServletException;

public class AccountControllerTest {

	private AccountController ac_instance;
	private StubHttpServletRequest http_request;
	private StubHttpServletResponse http_response;
	
	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		System.out.println("Starting unit tests of AccountController.java");
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		System.out.println("Stoping unit tests of AccountController.java");
	}

	@Before
	public void setUp() throws Exception {

		ac_instance = new AccountController();
		http_request = new StubHttpServletRequest();
		http_response = new StubHttpServletResponse();
	}
	
	@After
	public void tearDown() throws Exception {
		//Nothing to do
	}
	
	@Test
	public void TC_AC_01_doGet_SuccessfulUserRegisteration_GivenCorrectRegistrationInformation() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setAction("register");
		ac_instance.setRegistration(new Registration(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserRegisteration", "welcome.jsp", http_response.getRedirect());
	}
	
	@Test
	public void TC_AC_02_doGet_FailedUserRegisteration_GivenEmailAccountAlreadyInUse() throws ServletException, IOException {
		//Setup
		http_request.setState("Jane", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setAction("register");
		ac_instance.setRegistration(new Registration(false));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("FailedUserRegisteration - message", "Email already taken   \n Please use another email", http_request.getAttribute("message").toString());
		assertEquals("FailedUserRegisteration - destination", "registration.jsp", http_request.getDestination());
	}

	@Test
	public void TC_AC_03_doGet_SuccessfulUserLogin_GivenProperCredentials() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setParameter("username", "ironman");
		http_request.setAction("login");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "a"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_04_doGet_SuccessfulAdminUserLogin_GivenProperCredentials() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setParameter("username", "ironman");
		http_request.setAction("login");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
		
	@Test
	public void TC_AC_05_doGet_FailedUserLogin_GivenMissingUsername() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setParameter("username", "");
		http_request.setAction("login");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "a"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("FailedUserLogin - message", "Please enter Email and Password", http_request.getAttribute("message").toString());
		assertEquals("FailedUserLogin - destination", "welcome.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_06_doGet_FailedUserLogin_IncorrectUsernamePassword() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "wrongpass");
		http_request.setParameter("username", "ironman");
		http_request.setAction("login");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "a"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(false));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("FailedUserLogin - message", "Invalid email/password combination", http_request.getAttribute("message").toString());
		assertEquals("FailedUserLogin - destination", "welcome.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_07_doGet_SuccessfulUserLogout_GivenLogoutAction() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setParameter("username", "ironman");
		http_request.setAction("logout");
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogout - destination", "welcome.jsp", http_response.getRedirect());
	}
		
	@Test
	public void TC_AC_08_doGet_SuccessfulResetPassword_GiveResetAction() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setParameter("username", "ironman");
		http_request.setAction("reset");
		ac_instance.setPasswordReset(new PasswordReset(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulResetPassword - destination", "welcome.jsp", http_response.getRedirect());
	}
		
	@Test
	public void TC_AC_09_doGet_FailedResetPassword_GiveResetAction() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setParameter("username", "ironman");
		http_request.setAction("reset");
		ac_instance.setPasswordReset(new PasswordReset(false));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("FailedResetPassword - message", "Email entered is not registered \n Please try again", http_request.getAttribute("message").toString());
		assertEquals("FailedResetPassword - destination", "passwordReset.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_10_doGet_SuccessfulMakeUserAdmin_GivenMakeAdminAction() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setParameter("username", "ironman");
		http_request.setAction("makeAdmin");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "showNonAdmin.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_11_doGet_SuccessfulSubmitAdmin_GivenSubmitAdminActionAndSuperAdminUser() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		String[] selections = new String[1];
		selections[0] = "ironman";
		http_request.setParameterValues(selections);
		http_request.setAction("submitAdmin");
		http_request.putHttpSessionAttribute("privileges", "s");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_12_doGet_SuccessfulSubmitAdmin_GivenSubmitAdminActionAndNormalAdminUser() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		String[] selections = new String[1];
		selections[0] = "ironman";
		http_request.setParameterValues(selections);
		http_request.setAction("submitAdmin");
		http_request.putHttpSessionAttribute("privileges", "a");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
		
	@Test
	public void TC_AC_13_doGet_FailedSubmitAdmin_GivenSubmitAdminActionAndSuperAdminUserAndNoUserSelected() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setAction("submitAdmin");
		http_request.putHttpSessionAttribute("privileges", "s");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_14_doGet_FailedSubmitAdmin_GivenSubmitAdminActionAndNormalAdminUserAndNoUserSelected() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setAction("submitAdmin");
		http_request.putHttpSessionAttribute("privileges", "a");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_15_doPost_SuccessfulAdminRequestSubmit_GivenRequestSubmitActionAndNormalAdminUsers() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setAction("requestSubmit");
		
		http_request.setParameter("totalRequest", "2");
		http_request.setParameter("decision1", "approve");
		http_request.setParameter("username1", "ironman");
		http_request.setParameter("decision2", "deny");
		http_request.setParameter("username2", "batman");
		
		http_request.putHttpSessionAttribute("privileges", "a");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doPost(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_16_doPost_SuccessfulAdminRequestSubmit_GivenRequestSubmitActionAndSuperAdminUsers() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		http_request.setAction("requestSubmit");
		
		http_request.setParameter("totalRequest", "1");
		http_request.setParameter("decision1", "approve");
		http_request.setParameter("username1", "ironman");
		
		http_request.putHttpSessionAttribute("privileges", "s");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doPost(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "home.jsp", http_request.getDestination());
	}
	
	@Test
	public void TC_AC_17_doPost_SuccessfulAdminRequest_GivenAttributeTypeAsAdminRequest() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		
		http_request.setParameter("type", "adminRequest");
		http_request.putHttpSessionAttribute("username", "ironman");
		http_request.putHttpSessionAttribute("fname", "John");
		http_request.putHttpSessionAttribute("lname", "Doe");
		
		http_request.putHttpSessionAttribute("privileges", "s");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doPost(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("SuccessfulUserLogin", "Your request has been sent!", ac_instance.getAdministration().getRequest());
	}
	
	@Test
	public void TC_AC_18_doPost_SuccessfulAdminRequest_GivenAttributeTypeAsLink() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		
		http_request.setParameter("type", "link");
		http_request.putHttpSessionAttribute("username", "ironman");
		http_request.putHttpSessionAttribute("fname", "John");
		http_request.putHttpSessionAttribute("lname", "Doe");
		
		http_request.putHttpSessionAttribute("privileges", "s");
		ac_instance.setRegistration(new Registration(false));
		ac_instance.setUserRow(new getUserRow("John", "Doe", "John@gmail.com", "s"));
		ac_instance.setCommentsInfo(new getCommentsInfo());
		ac_instance.setLogInOut(new LogInAndOut(true));
		ac_instance.setAdministration(new StubAdministration(true));
		
		//Execute
		try{
			ac_instance.doPost(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		//assertEquals("SuccessfulUserLogin", "Your request has been sent!", ac_instance.getAdministration().getRequest());
	}
	
}
