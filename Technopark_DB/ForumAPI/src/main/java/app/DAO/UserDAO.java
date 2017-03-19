package app.DAO;

import app.Application;
import app.models.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.dao.DuplicateKeyException;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;


@Service
@Transactional
public class UserDAO {

    final private JdbcTemplate template;

    @Autowired
    public UserDAO(JdbcTemplate template) {
        this.template = template;
    }

    public void createTable() {
        String query = new StringBuilder()
                .append("CREATE EXTENSION IF NOT EXISTS citext; ")
                .append("CREATE TABLE IF NOT EXISTS users ( ")
                .append("nickname CITEXT UNIQUE NOT NULL PRIMARY KEY, ")
                .append("fullname TEXT NOT NULL, ")
                .append("about TEXT NOT NULL, ")
                .append("email CITEXT UNIQUE NOT NULL); ")
                .toString();

        template.execute(query);
    }

    public void dropTable() {
        String query = new StringBuilder()
                .append("DROP TABLE IF EXISTS users ;").toString();

        template.execute(query);
    }


    public int createNewUser(User user) {
        String query = new StringBuilder()
                .append("INSERT INTO users(about, email, fullname, nickname) VALUES(?,?,?,?) ;").toString();

        try {
            template.update(query, user.getAbout(), user.getEmail(), user.getFullname(), user.getNickname());
        } catch (DuplicateKeyException e) {
            System.out.println(e.getMessage());
            return Application.ERROR_DUPLICATE;
        } catch (DataAccessException e) {
            System.out.println(e.getMessage());
            return Application.ERROR_UNDEFINED;
        }

        return Application.ERROR_OK;
    }

    public List<User> getDuplicates(User user) {
        String query = new StringBuilder()
                .append("SELECT * FROM users WHERE nickname = '?' OR email = '?';").toString();
        try {
            List<Map<String, Object>> results = template.queryForList(query, user.getNickname(), user.getEmail());
            ArrayList<User> duplicates = new ArrayList<>();
            for(Map<String, Object> res: results){
                duplicates.add(new User(
                        res.get("nickname").toString(), res.get("fullname").toString(),
                        res.get("about").toString(), res.get("email").toString()
                ));
            }
            return duplicates;
        } catch (EmptyResultDataAccessException e) {
            System.out.println(e.getMessage());
        }

        return null;
    }
}
