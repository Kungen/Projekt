----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:37:03 03/10/2011 
-- Design Name: 
-- Module Name:    motor - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

--Hall1 ligger på JB1
--Hall2 ligger på JB2
--Clk er signalet fra clk1
--toggle1 er et toggle signal fra BTN3

--motor1_power ligger på JD1
--motor1_direction ligger på JD2
--motor1_enable ligger på JD3
--motor2_power ligger på JC1
--motor2_direction ligger på JC2
--motor2_enable ligger på JC3

entity motor is
	port( pos_in	: in std_logic_vector (13 downto 0);
			Clk 		: in std_logic;
			toggle1 	: in std_logic;
			
			
			motor1_power : out std_logic;
			motor1_direction : inout std_logic := '0';
			motor1_enable : out std_logic := '1';
			motor2_power : out std_logic;
			motor2_direction : inout std_logic;
			motor2_enable : out std_logic
			);

end motor;

architecture Behavioral of motor is
	
	signal runing : integer range 0 to 50001 := 50001;
	signal show : std_logic_vector (3 downto 0) := "0000";
	signal pos : integer range 0 to 10000 := 0;

begin
	
	pos <= conv_integer(pos_in);
	
	with toggle1 select
	runing <= 50001 when '1',
				 12501 when others;
	
	motor2_power <= '0';
	motor2_direction <= '0';
	motor2_enable <= '0';

	process(Clk)
		--variable der sørger for at PWM signalet kører med 1KHz
		variable scale_count : integer range 0 to 50001 := 1;
	
	begin
		if rising_edge(Clk) then
			scale_count := scale_count+1;
			if scale_count = 50001 then
				scale_count := 1;
			end if;
			if scale_count < runing then
				if motor1_direction = '1' then
					motor1_power <= '0';
				else
					motor1_power <= '1';
				end if;
			else
				if motor1_direction = '1' then
					motor1_power <= '1';
				else
					motor1_power <= '0';
				end if;
			end if;
			
		end if;
	end process;
	
	process(Clk)
	
--	variable pos : integer range 0 to 360 := 180;
	variable state : std_logic_vector (1 downto 0) := "11";
	variable scale_count2 : integer range 0 to 5001 := 1;
	
	begin
		if rising_edge(Clk) then
			scale_count2 := scale_count2 + 1;
			if scale_count2 = 5001 then
				scale_count2 := 1;
				if pos = 9900 then
					motor1_enable <= '0';
				end if;
				if pos < 9900 then
					motor1_direction <= '0';
					motor1_enable <= '1';
				end if;
				if pos > 9900 then
					motor1_direction <= '1';
					motor1_enable <= '1';
				end if;
			end if;
		end if;
	end process;

end Behavioral;

