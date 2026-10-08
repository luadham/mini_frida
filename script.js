const pid = 37119;
const offset = BigInt(0x11C8);
pattach(pid, {
    onAttach: () => {
        log(`Attached From JS On PID = ${pid}`);
        log(`Attaching to offset`)
        attach(offset, {
            onEnter: (regs) => {
                change_reg_value("rax", BigInt(0x03));
                const changed_regs = get_regs();
                for (const item in changed_regs) {
                    log(`${item} = 0x${changed_regs[item].toString(16)}`)
                }
            },
            onLeave: (regs) => {
                
            }
        });
    }
});