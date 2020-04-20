package server;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;

@SpringBootApplication(scanBasePackages = {"common", "server"})
@EntityScan("common.entities")
public class Server
{
    public static void main(String[] args)
    {
        SpringApplication.run(Server.class, args);
    }
}
