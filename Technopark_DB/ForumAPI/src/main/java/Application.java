import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.context.properties.ConfigurationProperties;

@SpringBootApplication
@ConfigurationProperties("spring.datasource")
public class Application {

    public static void main(String[] args) {
        System.out.println();
        SpringApplication.run(Application.class, args);
    }
}
