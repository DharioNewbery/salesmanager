#ifndef HELP_HPP
#define HELP_HPP
#include "../src/Command.hpp"

namespace help {
    const auto listSales = "\n\
>> list --help (shows this message)\n\
\n\
>> list\n\
list all sales.\n\
\n\
>> list <integer start>\n\
list all subsequent sales.\n\
\n\
>> list <integer start> <integer end>\n\
list all elements in the interval.\n";

    const auto loadSales = "\n\
>> load --help (shows this message)\n\
\n\
>> load <filename>\n\
load all sales from the file.\n";

    const auto saveSales = "\
>> save --help (shows this message)\n\
\n\
>> save <filename>\n\
write all sales to the file.\n";
    
    const auto addSale = "\n\
>> add --help (shows this message)\n\
\n\
>> add\n\
Start a routine to add a new sale.\n\
\n\
>> add <string buyer> <string item> <string date> <int price>\n\
Add a new sale.\n";

    const auto clear = "\n\
>> clear --help (shows this message)\n\
\n\
>> clear\n\
clear the terminal\n";
    
    const auto removeSale = "\n\
>> remove --help (shows this message)\n\
\n\
>> remove <integer id>\n\
remove the sale with the specified id.\n";
}


class HelpCommand: public Command {
    void execute(SalesManager& sm, Vector<std::string> args) override {
        if (args.getSize() == 0) {
            std::cout << "Available commands:\n";
            for (const auto& pair : CommandRegistry::getCommands()) {
                std::cout << pair.first << "\n";
            }
            std::cout << "Type 'help <command>' for more details on a specific command.\n";
            return;
        }
    }
};

CommandRegistrator registerHelpCommand("help", new HelpCommand());

#endif