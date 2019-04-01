#ifndef NACHOS_MACHINE_SINGLESTEPPER__HH
#define NACHOS_MACHINE_SINGLESTEPPER__HH


/// Abstract interface for single-step objects.
class SingleStepper {
public:
    /// Returns whether to continue single-stepping or no.
    virtual bool Step() = 0;
};


#endif
