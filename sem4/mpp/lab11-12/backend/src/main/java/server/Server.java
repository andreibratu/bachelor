package server;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;

@SpringBootApplication(scanBasePackages = {"server"})
@EntityScan("server.entities")
public class Server
{
    public static void main(String[] args)
    {
        SpringApplication.run(Server.class, args);
    }
}
