library ieee;
use ieee.std_logic_1164.all;

entity LoginBoard is
port( passswitches : in std_logic_vector (7 downto 0); --8 switches to try PW
		login : in std_logic;
		okPw, okLogin : out std_logic );
end LoginBoard;

architecture dataflow of LoginBoard is
signal password : std_logic_vector (7 downto 0); --8 digit password
begin
password <= "00101010"; --correct password is set to "00101010"
	loginTry : process( login )
	begin
		if login = '0' then					--if user press login button, do this:
			if passswitches = password then 		--if user input correct password, set output okPw = high
				okPw <= '1';
				okLogin <= '0';
			elsif passswitches = "00000000" then --if user reset the inputs, set okLogin = high
				okLogin <= '1';
				okPw <= '0';
			else									--if not reset or correct password, set okPw and okLogin = low
				okPw <= '0';
				okLogin <= '0';
			end if;
		else										--if user doesn't press login button, keep outputs low
			okPw <= '0';
			okLogin <= '0';	
		end if;
	end process;
end dataflow;