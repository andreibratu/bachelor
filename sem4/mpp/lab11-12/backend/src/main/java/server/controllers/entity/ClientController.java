package server.controllers;

import common.entities.Client;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import server.controllers.base.EntityController;
import server.services.ClientEntityServiceImplementation;
import server.validators.ClientValidator;

@RestController
@RequestMapping("/clients")
public class ClientController extends EntityController<Client>
{
    @Autowired
    public ClientController(
            ClientEntityServiceImplementation serviceImplementation,
            ClientValidator clientValidator
    ) {
        super(serviceImplementation, clientValidator);
    }
}
