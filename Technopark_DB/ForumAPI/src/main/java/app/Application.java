package app;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Application {

    public static final int ERROR_OK = 0;
    public static final int ERROR_DUPLICATE = 1;
    public static final int ERROR_UNDEFINED = 2;

    public static void main(String[] args) {
        System.out.println();
        SpringApplication.run(Application.class, args);
    }
}
