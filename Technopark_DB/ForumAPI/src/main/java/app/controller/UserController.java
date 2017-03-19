package app.controller;

import app.Application;
import app.DAO.UserDAO;
import app.models.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@RestController
@RequestMapping(path = "/api/user")
public class UserController {

    final private UserDAO userDAO;

    @Autowired
    public UserController(UserDAO userDAO){
        this.userDAO = userDAO;
    }

    @RequestMapping(path = "/{nickname}/create", method = RequestMethod.POST)
    public ResponseEntity createUser(@PathVariable(name = "nickname") String nickname,
                                     @RequestBody User user){
        if(!user.isCorrect() || !nickname.equals(user.getNickname())){
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).build();
        }

        int code = userDAO.createNewUser(user);

        if(code == Application.ERROR_DUPLICATE){
            List<User> duplicates = userDAO.getDuplicates(user);
            return ResponseEntity.status(HttpStatus.CONFLICT).body(duplicates);
        }
        if(code == Application.ERROR_UNDEFINED){
            return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
        }
        return ResponseEntity.status(HttpStatus.CREATED).body(user);
    }
}
