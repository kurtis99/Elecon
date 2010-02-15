#ifndef FLOATNUMBER_H
    #define FLOATNUMBER_H

    class FloatNumber
    {
        public:
            int16_t num;    /// Число
            uint8_t base;   /// Место десятичного разделителя
            FloatNumber()
            : num ( 0 ),
            base ( 2 )
                {};
            FloatNumber( int16_t _num )
            : base ( 2 )
                {
                    num = _num;
                };
            FloatNumber( int16_t _num, uint8_t _base )
                {
                    num = _num;
                    base = _base;
                };
    };

#endif /* FLOATNUMBER_H */