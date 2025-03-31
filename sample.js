import ine from "./ine.js";
import fs from "fs";

const sourceCode = fs.readFileSync("./sample.ine", "utf-8");
ine(sourceCode);