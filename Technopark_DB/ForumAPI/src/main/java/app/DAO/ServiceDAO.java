package app.DAO;

import app.models.Status;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;


@Service
@Transactional
public class ServiceDAO {

    final private JdbcTemplate template;
    final private UserDAO userDAO;

    @Autowired
    public ServiceDAO(JdbcTemplate template, UserDAO userDAO){

        this.template = template;
        this.userDAO = userDAO;
        dropAllTables();
        createAllTables();
    }

    public void createAllTables(){
        userDAO.createTable();
    }

    public void dropAllTables(){
        userDAO.dropTable();
    }

    public Status getStatus(){
        return null;
        //return new Status(userDAO.getCount(), forumDAO.getCount(), threadDAO.getCount(), postDAO.getCount());
    }

}
