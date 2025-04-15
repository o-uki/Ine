import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.function.Function;
import java.util.List;

class IneRun {
    public static void main(String[] args) {
        try {
            // ファイル読み込み
            List<String> sourceCode = Files.readAllLines(Path.of("sample.ine"));
            System.out.print(sourceCode + "\n");

            // PC
            int programCount = 0;

            // 順序記号の配列
            FlowCommand flowCommands[] = new FlowCommand[3];
            flowCommands[0] = new FlowCommand("I", "sequence");
            flowCommands[1] = new FlowCommand("?", "selection");
            flowCommands[2] = new FlowCommand("+", "join");

            System.out.print(flowCommands[0].name);

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