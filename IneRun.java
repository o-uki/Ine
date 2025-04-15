import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.function.Function;
import java.util.List;

class FlowCommand {
    public String token;
    public String name;

    public FlowCommand(String setToken, String setName) {
        this.token = setToken;
        this.name = setName;
    }
}

public class IneRun {
    public static void main(String[] args) {
        try {
            // ファイル読み込み
            List<String> sourceCode = Files.readAllLines(Path.of("sample.ine"));

            // PC
            int programCount = 0;

            // 順序コマンド
            FlowCommand flowCommands[] = new FlowCommand[3];
            flowCommands[0] = new FlowCommand("I", "sequence");
            flowCommands[1] = new FlowCommand("?", "selection");
            flowCommands[2] = new FlowCommand("+", "join");

            while (programCount < sourceCode.size()) {
                programCount++;
            }

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