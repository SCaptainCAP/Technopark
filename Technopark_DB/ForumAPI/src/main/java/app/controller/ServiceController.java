package app.controller;

import app.DAO.ServiceDAO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping(path = "/api/service")
public class ServiceController {

    final private ServiceDAO serviceDAO;

    @Autowired
    public ServiceController(ServiceDAO serviceDAO){
        this.serviceDAO = serviceDAO;
    }

    @RequestMapping(path = "/clear", method = RequestMethod.POST)
    public ResponseEntity clear(){
        serviceDAO.dropAllTables();
        serviceDAO.createAllTables();
        return ResponseEntity.status(HttpStatus.OK).build();
    }

    @RequestMapping(path = "/status", method = RequestMethod.GET)
    public ResponseEntity getStatus(){
        return ResponseEntity.ok(serviceDAO.getStatus());
    }
}
