package lab7;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.ServletComponentScan;
import org.springframework.transaction.annotation.EnableTransactionManagement;

@ServletComponentScan
@SpringBootApplication
public class Lab7Application
{
	public static void main(String[] args) {
		SpringApplication.run(Lab7Application.class, args);
	}
}
