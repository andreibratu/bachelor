package client.services;

import common.services.EntityService;
import common.services.ReportingService;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.remoting.httpinvoker.HttpInvokerProxyFactoryBean;

@Configuration
public class ServiceConfiguration
{
    @Value("${server.root}")
    private String serverRoot;

    @Bean("movieService")
    public HttpInvokerProxyFactoryBean movieInvoker()
    {
        HttpInvokerProxyFactoryBean invoker = new HttpInvokerProxyFactoryBean();
        invoker.setServiceUrl(serverRoot + "movie");
        invoker.setServiceInterface(EntityService.class);
        return invoker;
    }

    @Bean("clientService")
    public HttpInvokerProxyFactoryBean clientInvoker()
    {
        HttpInvokerProxyFactoryBean invoker = new HttpInvokerProxyFactoryBean();
        invoker.setServiceUrl(serverRoot + "client");
        invoker.setServiceInterface(EntityService.class);
        return invoker;
    }

    @Bean("rentalService")
    public HttpInvokerProxyFactoryBean rentalInvoker()
    {
        HttpInvokerProxyFactoryBean invoker = new HttpInvokerProxyFactoryBean();
        invoker.setServiceUrl(serverRoot + "rental");
        invoker.setServiceInterface(EntityService.class);
        return invoker;
    }

    @Bean("reportingService")
    public HttpInvokerProxyFactoryBean reportingInvoker()
    {
        HttpInvokerProxyFactoryBean invoker = new HttpInvokerProxyFactoryBean();
        invoker.setServiceUrl(serverRoot + "reporting");
        invoker.setServiceInterface(ReportingService.class);
        return invoker;
    }
}
