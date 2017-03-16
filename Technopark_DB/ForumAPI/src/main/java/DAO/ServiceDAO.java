package DAO;

import models.Status;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

/**
 * Created by algys on 24.02.17.
 */


@Service
@Transactional
public class ServiceDAO {

    final private JdbcTemplate template;
    final private UserDAO userDAO;
    final private ForumDAO forumDAO;
    final private ThreadDAO threadDAO;
    final private PostDAO postDAO;
    final private VoteDAO voteDAO;

    @Autowired
    public ServiceDAO(JdbcTemplate template, UserDAO userDAO,
                      ForumDAO forumDAO, ThreadDAO threadDAO,
                      PostDAO postDAO, VoteDAO voteDAO){

        this.template = template;
        this.userDAO = userDAO;
        this.forumDAO = forumDAO;
        this.threadDAO = threadDAO;
        this.postDAO = postDAO;
        this.voteDAO = voteDAO;
        dropTables();
        createTables();
    }

    public void createTables(){
        userDAO.createTable();
        forumDAO.createTable();
        threadDAO.createTable();
        postDAO.createTable();
        voteDAO.createTable();
    }

    public void dropTables(){
        voteDAO.dropTable();
        postDAO.dropTable();
        threadDAO.dropTable();
        forumDAO.dropTable();
        userDAO.dropTable();
    }

    public void truncateTables(){
        voteDAO.truncateTable();
        postDAO.truncateTable();
        threadDAO.truncateTable();
        forumDAO.truncateTable();
        userDAO.truncateTable();
    }

    public Status getStatus(){
        return new Status(userDAO.getCount(), forumDAO.getCount(), threadDAO.getCount(), postDAO.getCount());
    }

}
