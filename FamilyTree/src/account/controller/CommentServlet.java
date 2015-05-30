package account.controller;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import account.models.MakeReplay;

/**
 * Servlet implementation class CommentServlet
 */
public class CommentServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public CommentServlet() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		// doLogin
		HttpSession session = request.getSession(true);
		
		if (request.getParameter("type").equalsIgnoreCase("reply")) {

			int parent = Integer.parseInt(request.getParameter("id"));
			String text = request.getParameter("text");


			MakeReplay.postReplay(parent, text, session
					.getAttribute("username").toString());
		}else if(request.getParameter("type").equalsIgnoreCase("comment")){
			String text = request.getParameter("text");			

			int result = MakeReplay.postComment(text, session
					.getAttribute("username").toString());

			response.getWriter().write(String.valueOf(result));
			
		}else if(request.getParameter("type").equalsIgnoreCase("getnewcomment")){
			int total_comments = Integer.parseInt(request.getParameter("total_comments"));
			
			String json = MakeReplay.getLast(total_comments);
			response.getWriter().write(json);
		}
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub

	}

}
