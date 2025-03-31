export default (sourceCode) => {
    const flowCommands = [
        ["sequence", "I"],
        ["selection", "?"],
        ["end", "X"]
    ]

    let commands = sourceCode.split(/\n/);
    let readIndex = 0;

    const commandRead = () => {
        const command = commands[readIndex];
    }
}