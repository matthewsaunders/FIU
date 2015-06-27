package administration.Controllertest;

import static org.junit.Assert.*;

import org.junit.*;
import org.mockito.Mockito;

import account.controllertest.*;
import account.modelstest.*;

import java.io.IOException;
import java.sql.SQLException;
import java.util.*;
//import java.sql.DriverManager;


public class AdministrationTest  {
	
	private ArrayList<User> admins ; 
	
	private Administration a_instance;
	
	private DriverManager manager ;
	
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
		
		 admins = new ArrayList<User>() ;
		 
		 a_instance = new Administration() ;
	}
	
	@After
	public void tearDown() throws Exception {
		System.out.println("Stoping unit tests...");
	}
	
	@Test
	public void test_NoAdmin_NoAdministratorGivenEmptyList() throws Exception{
		
		ArrayList<User> test = new ArrayList<User>();
		
		try{
			admins = a_instance.findNoAdmin();
		}catch(Exception e){
			System.out.println(e);
		}
		
		assertEquals("Rainy Path 1", test, admins);
	}
	
	@Test
	public void test_NoAdmin_CorrectFnameNoAdministratorGivenList() throws Exception{
		
		ArrayList<User> test = new ArrayList<User>();
		
		ResultSet please = new ResultSet();
		PreparedStatement please1 = new PreparedStatement() ;
		please1.setQueryResult(please);
		Connection please2 = new Connection() ;
		please2.setPreparedStatement(please1) ;
		manager = new DriverManager() ;
		manager.setConnection(please2);
		a_instance.setDriverManager(manager);
		
		try{
			admins = a_instance.findNoAdmin();
					
		}catch(Exception e){
			System.out.println(e);
		}
		
		User user1 = admins.get(0) ;
		
		String result = user1.getFname() ;
		
		assertEquals("Happy Path 1", result, "fname");
	}
	
	@Test
	public void test_NoAdmin_CorrectLnameNoAdministratorGivenList() throws Exception{
		
		ArrayList<User> test = new ArrayList<User>();
		
		ResultSet please = new ResultSet();
		PreparedStatement please1 = new PreparedStatement() ;
		please1.setQueryResult(please);
		Connection please2 = new Connection() ;
		please2.setPreparedStatement(please1) ;
		manager = new DriverManager() ;
		manager.setConnection(please2);
		a_instance.setDriverManager(manager);
		
		try{
			admins = a_instance.findNoAdmin();
					
		}catch(Exception e){
			System.out.println(e);
		}
		
		User user1 = admins.get(0) ;
		
		String result = user1.getLname() ;
		
		assertEquals("Happy Path 2", result, "lname");
	}
	
	@Test
	public void test_makeAdmin_MakeAdministratorGivenCorrectInput() throws Exception{
		
		boolean prove = false ;
		
		ArrayList<User> test = new ArrayList<User>();
		User user1 = new User("Flesh1", "Hannibal", "Lecter", "a");
		User user2 = new User("Life2", "Anakin", "Skywalker", "a");
		User user3 = new User("Mother3", "Norman", "Bates", "u");
		User user4 = new User("Status4", "Keyzer", "Soze", "a");
		test.add(user1);
		test.add(user2);
		test.add(user3);
		test.add(user4);
		
		try{
			prove = a_instance.makeAdmin(test);
		}catch(Exception e){
			System.out.println(e);
		}
		
		assertEquals("Happy Path 3", prove, true);
		
	}
	
	@Test
	public void test_makeAdmin_MakeAdministratorEmptyList() throws Exception{
		
		boolean prove = true ; 
		
		ArrayList<User> test = new ArrayList<User>();
		
		try{
			prove = a_instance.makeAdmin(test);
		}catch(Exception e){
			System.out.println(e);
		}
		
		assertEquals("Rainy Path 2", prove, false);
		
	}
	
	@Test
	public void test_sendRequest_SendRequestGivenCorrectInput() throws Exception{
		
		
		String request = "" ;
		
		
		try{
			request = a_instance.sendRequest("Love","Miss","Piggy");
		}catch(Exception e){
			System.out.println(e);
		}
		
		
		assertEquals("Happy Path 4", request, "Your request has been sent!");
	}
	
	@Test
	public void test_showAdminRequest_ShowAdminRequestGivenEmptyList() throws Exception{
		
		ArrayList<User> test = new ArrayList<User>();
		
		try{
			admins = a_instance.showAdminRequest();
		}catch(Exception e){
			System.out.println(e);
		}
		
		assertEquals("Rainy Path 3", admins, test);
		
	}
	
	@Test
	public void test_showAdminRequest_ShowFnameAdminRequestGivenList() throws Exception{
		
		ArrayList<User> test = new ArrayList<User>();
		
		ResultSet please = new ResultSet();
		PreparedStatement please1 = new PreparedStatement() ;
		please1.setQueryResult(please);
		Connection please2 = new Connection() ;
		please2.setPreparedStatement(please1) ;
		manager = new DriverManager() ;
		manager.setConnection(please2);
		a_instance.setDriverManager(manager);
			
		try{
			admins = a_instance.showAdminRequest();
			
		}catch(Exception e){
			System.out.println(e);
		}
		
		User user5 = admins.get(0) ;
		
		String result = user5.getUserName() ;
		
		assertEquals("Happy Path 5", result, "requested_by");
		
	}
	
	/*
	 * JUnit test that generates an arrayList of users and passes it as a parameter of method 
	 * dropFromTable. It tests whether at the end, the arrayList is empty.
	 */
	@Test
	public void test_dropFromTable_DropUserGivenUserList() throws Exception{
		
		//ArrayList to pass with dummy values in it.
		ArrayList<User> test = new ArrayList<User>();
		User user1 = new User("Flesh1", "Hannibal", "Lecter", "a");
		User user2 = new User("Life2", "Anakin", "Skywalker", "a");
		User user3 = new User("Mother3", "Norman", "Bates", "u");
		User user4 = new User("Status4", "Keyzer", "Soze", "a");
		test.add(user1);
		test.add(user2);
		test.add(user3);
		test.add(user4);
		
		//Empty arrayList to test.
		ArrayList<User> test1 = new ArrayList<User>() ;
		
		try{
			//Instance of Administration.java that calls the method to test.
			a_instance.dropFromTable(test);
		}catch(Exception e){
			System.out.println(e);
		}
		
		//Testing for equality of two empty ArrayLists.
		assertEquals("Happy Path 6", test, test1);
			
	}
	
	@Test
	public void test_dropFromTable_DropUserGivenEmptyList() throws Exception{
		
		
		ArrayList<User> test = new ArrayList<User>();
		
		ArrayList<User> test1 = new ArrayList<User>() ;
		
		try{
			a_instance.dropFromTable(test);
		}catch(Exception e){
			System.out.println(e);
		}
		
		assertEquals("Rainy Path 4", test, test1);
			
	}

}
