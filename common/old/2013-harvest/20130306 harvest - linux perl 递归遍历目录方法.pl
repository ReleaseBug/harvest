
Linux perl ����Ŀ¼���ļ��ķ���:


1��ʹ��bash���
    
    #�ݹ����Ŀ¼�µ�����c��h�ļ� Ӧ�ø�perl�ű�
    $ du -a | awk -v IGNORECASE=1 'sub(/^[.0-9A-Z]+\s+/, ""){}; gsub(/ /, "\\ "){}; /\.((h)|(c))/' | xargs perl -i $0

    #perl �д��룺ע��perl�� -iѡ����ô����еı�׼�������ǰ�ļ���
    while(<>)
    {
        if(//)
        {
            print;
        }
    }

2��ʹ�ô��룺
sub listdir { 
    my @arr, $j = 0;
    for($i=0;$i<=$#_;$i++) {
        if(-d $_[$i]) {
            if(opendir($handle, $_[$i])) {
                while($dir = readdir($handle)) {
                    if(!($dir =~ m/^\.$/) and !($dir =~ m/^(\.\.)$/)) {
                        print "$dir";
                        if(-d $_[$i]."\\$dir") {
                            $arr[$j++] = $_[$i]."\\$dir";
                            print "\t[DIR]"
                        }
                        print "\n";
                    }
                }
                closedir($handle);
            }
        }
    }
    if($j>0) {
        listdir (@arr);
    }
}
listdir 'D:\Fun\CS 1.6\platform\Steam';
