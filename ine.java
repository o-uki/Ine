import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
// import java.util.function.Function;
import java.util.List;

class IneRun {
    public static void main(String[] args) {
        try {
            List<String> sourceCode = Files.readAllLines(Path.of("sample.ine"));
            System.out.print(sourceCode + "\n");

            // Function<String, Integer> runner = (str) -> {
            //     System.out.print(Integer.parseInt(str));
            //     return Integer.parseInt(str) + 10;
            // };

            // System.out.print(runner.apply("120"));
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }
}