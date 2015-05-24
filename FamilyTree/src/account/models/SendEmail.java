package account.models;

import java.util.Properties;

import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

//import account.models.PasswordReset.MyAuthenticator;

public class SendEmail {
	
	public static void send(String email, String name, String subject, String text)
		throws MessagingException, AddressException {
			/*
			 * It is a good practice to put this in a java.util.Properties file and
			 * encrypt password. Scroll down to comments below to see how to use
			 * java.util.Properties in JSF context.
			 */
			String senderEmail = "famtreeservices@gmail.com";
			String senderMailPassword = "1234test";
			String gmail = "smtp.gmail.com";

			Properties props = System.getProperties();

			props.put("mail.smtp.user", senderEmail);
			props.put("mail.smtp.host", "smtp.gmail.com");
			props.put("mail.smtp.port", "465");
			props.put("mail.smtp.starttls.enable", "true");
			props.put("mail.smtp.debug", "true");
			props.put("mail.smtp.auth", "true");
			props.put("mail.smtp.socketFactory.port", "465");
			props.put("mail.smtp.socketFactory.class",
					"javax.net.ssl.SSLSocketFactory");
			props.put("mail.smtp.socketFactory.fallback", "false");

			// Required to avoid security exception.
			MyAuthenticator authentication = new MyAuthenticator(senderEmail,
					senderMailPassword);
			Session session = Session.getDefaultInstance(props, authentication);
			session.setDebug(true);

			MimeMessage message = new MimeMessage(session);

			BodyPart messageBodyPart = new MimeBodyPart();

			String output = "Hello "
					+ name
					+ ",\n\n"
					+ text
					+ "\n\n"
					+ "Thank you for using our services."
					+ "\n \n \n\nFamily Tree Account Services";

			messageBodyPart.setText(output);

			// Add message text
			Multipart multipart = new MimeMultipart();
			multipart.addBodyPart(messageBodyPart);

			message.setContent(multipart);
			message.setSubject(subject);
			message.setFrom(new InternetAddress(senderEmail));
			message.addRecipient(Message.RecipientType.TO, new InternetAddress(
					email));

			Transport transport = session.getTransport("smtps");
			transport.connect(gmail, 465, senderEmail, senderMailPassword);
			transport.sendMessage(message, message.getAllRecipients());

			transport.close();

		
	}
	
	private static class MyAuthenticator extends javax.mail.Authenticator {
		String User;
		String Password;

		public MyAuthenticator(String user, String password) {
			User = user;
			Password = password;
		}

		@Override
		public PasswordAuthentication getPasswordAuthentication() {
			return new javax.mail.PasswordAuthentication(User, Password);
		}
	}
	
}
