package server.controllers.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import server.controllers.base.BaseEntityController;
import server.entities.Client;
import server.services.entity.ClientEntityServiceImplementation;
import server.validators.ClientValidator;

@RestController
@RequestMapping("/clients")
public class ClientController extends BaseEntityController<Client>
{
    @Autowired
    public ClientController(
            ClientEntityServiceImplementation serviceImplementation,
            ClientValidator clientValidator
    ) {
        super(serviceImplementation, clientValidator);
    }
}
