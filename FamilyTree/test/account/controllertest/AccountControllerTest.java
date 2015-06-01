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
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
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
	public void doGet_UserRegisters_GivenCorrectRegistrationInformation() throws ServletException, IOException {
		//Setup
		http_request.setState("John", "Doe", "John@gmail.com", "JohnyBoy");
		ac_instance.setRegistration(new StubRegistration());
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("Happy Path 1", "welcome.jsp", http_response.getRedirect());
	}
	
	@Test
	public void doGet_UserRegisters_GivenCorrectRegistrationInformation2() throws ServletException, IOException {
		//Setup
		http_request.setState("Jane", "Doe", "Jane@gmail.com", "jarule123");
		ac_instance.setRegistration(new StubRegistration());
		
		//Execute
		try{
			ac_instance.doGet(http_request, http_response);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Evaluate
		assertEquals("Happy Path 1", "welcome.jsp", http_response.getRedirect());
	}
	
}
