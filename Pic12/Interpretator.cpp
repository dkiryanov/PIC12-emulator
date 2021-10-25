#include "stdafx.h"
#include "Interpretator.h"
#include "Macroces.h"

Interpretator::Interpretator()
{
}

Interpretator::~Interpretator()
{
}

void Interpretator::Interpret(Processor& processor)
{
	short data = processor.GetCurrentData();

	switch (GetBit(data, 13))
	{
		case 0:															// 0xxxxxxxxxxxxx
			switch (GetBit(data, 12))
			{
			case 0:														// 00xxxxxxxxxxxx
				switch (GetBit(data, 11))
				{
				case 0:													// 000xxxxxxxxxxx
					switch (GetBit(data, 10))
					{
					case 0:												// 0000xxxxxxxxxx
						switch (GetBit(data, 9))
						{
						case 0:											// 00000xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 000000xxxxxxxx
								switch (GetBit(data, 7))
								{
								case 0:									// 0000000xxxxxxx
									switch (GetBit(data, 6))
									{
									case 0:								// 00000000xxxxxx
										switch (GetBit(data, 5))
										{
										case 0:							// 000000000xxxxx
											switch (GetBit(data, 4))
											{
											case 0:						// 0000000000xxxx
												switch (GetBit(data, 3))
												{
												case 1:					// 00000000001xxx
													switch (GetBit(data, 2))
													{
													case 0:				// 000000000010xx
														switch (GetBit(data, 1))
														{
														case 0:			// 0000000000100x
															switch (GetBit(data, 0))
															{
															case 0:		// 00000000001000
																processor.RETURN();
																break;
															case 1:		// 00000000001001
																processor.RETFIE();
																break;
															}
															break;
														}
														break;
													}
													break;
												}
												break;
											}
											break;
										}
										break;
									case 1:								// 00000001xxxxxx
										switch (GetBit(data, 5))
										{
										case 1:							// 000000011xxxxx
											switch (GetBit(data, 4))
											{
											case 0:						// 0000000110xxxx
												switch (GetBit(data, 3))
												{
												case 0:					// 00000001100xxx
													switch (GetBit(data, 2))
													{
													case 0:				// 000000011000xx
														switch (GetBit(data, 1))
														{
														case 1:			// 0000000110001x
															switch (GetBit(data, 0))
															{
															case 1:		// 00000001100011
																processor.SLEEP();
																break;
															}
															break;
														}
														break;
													case 1:				// 000000011001xx
														switch (GetBit(data, 1))
														{
														case 0:			// 0000000110010x
															switch (GetBit(data, 0))
															{
															case 0:		// 00000001100100
																processor.CLRWDT();
																break;
															}
															break;
														}
														break;
													}
													break;
												}
												break;
											}
											break;
										}
										break;
									}

									switch (GetBit(data, 4))
									{
									case 0:								// 0000000xx0xxxx
										switch (GetBit(data, 3))
										{
										case 0:							// 0000000xx00xxx
											switch (GetBit(data, 2))
											{
											case 0:						// 0000000xx000xx
												switch (GetBit(data, 1))
												{
												case 0:					// 0000000xx0000x
													switch (GetBit(data, 0))
													{
													case 0:				// 0000000xx00000
														processor.NOP();
														break;
													}
													break;
												}
												break;
											}
											break;
										}
										break;
									}
									break;

								case 1:									// 0000001xxxxxxx
									processor.MOVWF(GetBit(data, 7), GetSevenBitsValue(data));
									break;
								}
								break;
							case 1:										// 000001xxxxxxxx
								switch (GetBit(data, 7))
								{
								case 0:									// 0000010xxxxxxx
									processor.CLRW();
									break;
								case 1:									// 0000011xxxxxxx
									processor.CLRF(GetBit(data, 7), GetSevenBitsValue(data));
									break;
								}
								break;
							}
							break;
						case 1:											// 00001xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 000010xxxxxxxx
								processor.SUBWF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							case 1:										// 000011xxxxxxxx
								processor.DECF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							}
							break;
						}
						break;
					case 1:												// 0001xxxxxxxxxx
						switch (GetBit(data, 9))
						{
						case 0:											// 00010xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 000100xxxxxxxx
								processor.IORWF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							case 1:										// 000101xxxxxxxx
								processor.ANDWF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							}
							break;
						case 1:											// 00011xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 000110xxxxxxxx
								processor.XORWF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							case 1:										// 000111xxxxxxxx
								processor.ADDWF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							}
							break;
						}
						break;
					}
					break;
				case 1:													// 001xxxxxxxxxxx
					switch (GetBit(data, 10))
					{
					case 0:												// 0010xxxxxxxxxx
						switch (GetBit(data, 9))
						{
						case 0:											// 00100xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 001000xxxxxxxx
								processor.MOVF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							case 1:										// 001001xxxxxxxx
								processor.COMF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							}
							break;
						case 1:											// 00101xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 001010xxxxxxxx
								processor.INCF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							case 1:										// 001011xxxxxxxx
								processor.DECFSZ(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							}
							break;
						}
						break;
					case 1:												// 0011xxxxxxxxxx
						switch (GetBit(data, 9))
						{
						case 0:											// 00110xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 001100xxxxxxxx
								processor.RRF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							case 1:										// 001101xxxxxxxx
								processor.RLF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							}
							break;
						case 1:											// 00111xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 001110xxxxxxxx
								processor.SWAPF(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							case 1:										// 001111xxxxxxxx
								processor.INCFSZ(GetBit(data, 7), GetSevenBitsValue(data));
								break;
							}
							break;
						}
						break;
					}
					break;
				}
				break;
			case 1:														// 01xxxxxxxxxxxx
				switch (GetBit(data, 11))
				{
				case 0:													// 010xxxxxxxxxxx
					switch (GetBit(data, 10))
					{
					case 0:												// 0100xxxxxxxxxx
						processor.BCF(GetThreeBitsValue(data), GetSevenBitsValue(data));
						break;
					case 1:												// 0101xxxxxxxxxx
						processor.BSF(GetThreeBitsValue(data), GetSevenBitsValue(data));
						break;
					}
					break;
				case 1:													// 011xxxxxxxxxxx
					switch (GetBit(data, 10))
					{
					case 0:												// 0110xxxxxxxxxx
						processor.BTFSC(GetThreeBitsValue(data), GetSevenBitsValue(data));
						break;
					case 1:												// 0111xxxxxxxxxx
						processor.BTFSS(GetThreeBitsValue(data), GetSevenBitsValue(data));
						break;
					}
					break;
				}
				break;
			}
			break;
		case 1:															// 1xxxxxxxxxxxxx
			switch (GetBit(data, 12))
			{
			case 0:														// 10xxxxxxxxxxxx
				switch (GetBit(data, 11))
				{
				case 0:													// 100xxxxxxxxxxx
					processor.CALL(GetElevenBitsValue(data));
					break;
				case 1:													// 101xxxxxxxxxxx
					processor.GOTO(GetElevenBitsValue(data));
					break;
				}
				break;
			case 1:														// 11xxxxxxxxxxxx
				switch (GetBit(data, 11))
				{
				case 0:													// 110xxxxxxxxxxx
					switch (GetBit(data, 10))
					{
					case 0:												// 1100xxxxxxxxxx
						processor.MOVLW(GetEightBitsValue(data));
						break;
					case 1:												// 1101xxxxxxxxxx
						processor.RETLW(GetEightBitsValue(data));
						break;
					}
					break;
				case 1:													// 111xxxxxxxxxxx
					switch (GetBit(data, 10))
					{
					case 0:												// 1110xxxxxxxxxx
						switch (GetBit(data, 9))
						{
						case 0:											// 11100xxxxxxxxx
							switch (GetBit(data, 8))
							{
							case 0:										// 111000xxxxxxxx
								processor.IORLW(GetEightBitsValue(data));
								break;
							case 1:										// 111001xxxxxxxx
								processor.ANDLW(GetEightBitsValue(data));
								break;
							}
							break;
						case 1:	// 11101xxxxxxxxx
							switch (GetBit(data, 8))
							{
								case 0:	// 111010xxxxxxxx
									processor.XORLW(GetEightBitsValue(data));
									break;
								}
							break;
						}
						break;
					case 1: // 1111xxxxxxxxxx												
						switch (GetBit(data, 9))
						{
							case 0: // 11110xxxxxxxxx											
								processor.SUBLW(GetEightBitsValue(data));
								break;
							case 1:	// 11111xxxxxxxxx										
								processor.ADDLW(GetEightBitsValue(data));
								break;
						}
						break;
					}
					break;
				}
				break;
			}
			break;
	}
}