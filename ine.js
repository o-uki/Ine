export default (sourceCode) => {
    // フローコマンドのクラス
    class FlowCommand {
        constructor (command, type) {
            this.command = command,
            this.type = type
        }
    }

    // 関数コマンドのクラス
    class FunctionCommand {
        constructor (command, type, process) {
            this.command = command,
            this.type = type,
            this.process = process
        }
    }

    // フローコマンドの配列
    const flowCommands = [
        new FlowCommand("I", "sequence"),
        new FlowCommand("?", "selection"),
        new FlowCommand("+", "connect"),
        new FlowCommand("X", "end")
    ]

    // 関数コマンドの配列
    const functionCommands = [
        new FunctionCommand("wr", "write", (operands) => {
            console.log(...operands);

            return 1;
        }),
        new FunctionCommand("eq", "equal", (operands) => {
            if (operands[0] === operands[1]) {
                return 1;
            } else {
                return 0;
            }
        })
    ]

    let ineMemory = new Array(256);

    let rows = sourceCode.split(/\n/);
    let readRowIndex = 0;

    const functionCommandGet = (rowTokens) => {
        const rowFunctionCommands = rowTokens.slice(1, 3);
        let rowOperands;

        if (typeof rowFunctionCommands[1] != "undefined") {
            rowOperands = rowFunctionCommands[1].split(",");
        }

        for (let k = 0; k < functionCommands.length; k++) {
            if (rowFunctionCommands[0] === functionCommands[k].command) {
                return functionCommands[k].process(rowOperands);
            }
        }
    }

    const commandRead = () => {
        console.log(readRowIndex);
        const rowTokens = rows[readRowIndex].split(/ +/);

        // 何のフローコマンドか
        for (let j = 0; j < flowCommands.length; j++) {
            if (rowTokens[0] === flowCommands[j].command) {
                // フローコマンドによって処理を変える
                if (flowCommands[j].type === "sequence") {
                    functionCommandGet(rowTokens);
                    
                    readRowIndex++;
                    commandRead();
                } else if (flowCommands[j].type === "selection") {
                    
                }
            }
        }
    }

    commandRead();
}